#include "node_ctl.h"
#include "position.h"
#include "mavlink.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define QUERY_THRESHOLD 8
#define MAX_PKT_LEN 8

static struct node_list unknown_nodes;
static struct node_list queried_nodes;

static int pos_process_query_result (struct position_t* self, mavlink_message_t* msg);
static void pos_process_scan_result (struct position_t* self, bdaddr_t addr);

struct position_t* pos_init (struct ble_t* ble, struct comm_t* com)
{
    if (NULL == ble || NULL == com)
    {
        goto fail;
    }
    struct position_t* self = malloc (sizeof (struct position_t));

    self->ble = ble; 
    self->com = com;
    ASSERT (ble != NULL && com != NULL);

    node_list_init (&self->ready_list);
    node_list_init (&self->conn_list);
    node_list_init (&unknown_nodes);
    node_list_init (&queried_nodes);

    self->status = INIT;
    self->pos_valid = false;
    self->cur_x = self->cur_y = 200.0f;

    return self;

    fail:
        printf("init position failed!!\n");
        return NULL;
}

static void pos_process_scan_result (struct position_t* self, bdaddr_t addr)
{
    //ble object handle duplicates. 
    struct node_basic* node = node_create (addr, FOUND);
    node_insert (&unknown_nodes, node);
}

int pos_estimate_position (struct position_t* self, int timeout)
{
    struct list* conn_list = &self->ble->conn_list;
    if (list_empty (conn_list))
    {
        return -1;
    }

    struct node_basic* node = NULL;
    struct node_info* info = NULL;
    struct list_elem* end = list_end (conn_list);
    float weight_sum = 0.0f, norm_weight_sum = 0.0f;
    struct list temp_list;
    list_init (&temp_list);

    for (struct list_elem* e = list_front (conn_list); e != end;)
    {
        // filter invalid rssi nodes
        node = node_get_elem (e);
        info = node->info;
        if (info->rssi == 127)
        {
            e = list_remove (e);
            list_push_back (&temp_list, &node->elem);
            continue;
        }

        info->weight = sqrtf (powf(10.0f, ((float) info->rssi) / 10.0f)
                             );
        weight_sum += info->weight;        
        e = list_next (e);
    }

    if (list_empty (conn_list))
        goto recover;


    end = list_end (conn_list);
    int len = list_size (conn_list);
    for (struct list_elem* e = list_front (conn_list); e != end; e = list_next(e))
    {
        node = node_get_elem (e);
        info = node->info;
        info->weight = info->weight / weight_sum; // normalize weight

        info->weight = (info->weight * powf ((float) len, 2.0 * info->weight)); //improved weight
        norm_weight_sum += info->weight;
    }

    float est_x = 0.0f, est_y = 0.0f;
    
    for (struct list_elem* e = list_front (conn_list); e != end; e = list_next(e))
    {
        node = node_get_elem (e);
        info = node->info;

        info->weight = info->weight / norm_weight_sum; // final weight
        // now calc est pos
        est_x += info->weight * info->real_x;
        est_y += info->weight * info->real_y;
    }

    self->cur_x = est_x;
    self->cur_y = est_y;

    recover:
    if (!list_empty (&temp_list))
    {
        end = list_end (&temp_list);
        for (struct list_elem* e = list_front (&temp_list); e != end;)
        {
            node = node_get_elem (e);
            e = list_remove (e);

            list_push_back (conn_list, &node->elem);
        }        
    }

    node = node_get_elem (list_front (conn_list));
    info = node->info;
    
    return 0;
}

void pos_print_nodes (struct position_t* self, struct node_list* target)
{
    struct list* target_list = &target->head;
    if (list_empty (target_list))
        return;
    
    struct list_elem* end = list_end (target_list);
    struct list_elem* e = NULL;
    struct node_basic* cur;
    int cnt = 0;
    for (e = list_front (target_list);
         e != end;
         e = list_next (e))
    {
        cur = list_entry (e, struct node_basic, elem);
        printf("%s\t", batostr(&cur->addr));
    }
    printf("\n\n");
}

static int pos_process_query_result (struct position_t* self, mavlink_message_t* msg)
{
    mavlink_query_result_t res;
    mavlink_msg_query_result_decode (msg, &res);
    struct node_basic* node = NULL;
    struct node_info* info = NULL;
    bdaddr_t target_addr;

    if (bacmp (&self->ble->my_addr, res.addr) != 0)
    {
        return -1;//server error or pkt error
    }

    bacpy (&target_addr, res.match_addr);
    node = node_find (target_addr, &queried_nodes);

    if (0 == res.is_usable)
    {
        node_remove_frm_list (&queried_nodes, node);
        node_destroy (node);
        return 0;
    }


    if (NULL == node)
    {
        return -1;
    }

    node->status = READY;
    node = (struct node_basic*) node_promote(node);

    info = node->info;
    info->real_x = res.x;
    info->real_y = res.y;

    node_remove_frm_list (&queried_nodes, node);
    node_insert (&self->ready_list, node);
    
    return 0;
}

void pos_process_queries (struct position_t* self, int timeout)
{
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    int len;
    mavlink_message_t msg;
    mavlink_status_t status;


    len = comm_try_read (self->com , buf, MAVLINK_MAX_PACKET_LEN);
    if (len <= 0)
    {
        return;
    }

    for (int i = 0; i < len; i++)
    {
        if (mavlink_parse_char(MAVLINK_COMM_0, buf[i], &msg, &status))
        {
            switch (msg.msgid)
            {
            case MAVLINK_MSG_ID_heartbeat:
                break;
            case MAVLINK_MSG_ID_query_result:
                pos_process_query_result (self, &msg);
                break;
            case MAVLINK_MSG_ID_command:
                break;
            
            default:
                break;
            }
        }
    }
}

void pos_try_connect (struct position_t* self, int timeout)
{
    struct node_basic* node = NULL;
    struct node_info* info = NULL;
    struct list* conn_list = &self->conn_list.head;
    struct list* ready_list = &self->ready_list.head;

    if (list_empty(ready_list))
    {
        return;
    }

    if (list_size(ready_list) >= 16)
    {
        return;
    }

    node = node_get_elem (list_pop_front (ready_list));
    info = node->info;

    if (ble_try_connect (self->ble, node->addr, &info->handle, timeout) < 0)
    {
        ble_cancel_connect (self->ble, timeout);
        ble_reenable_scan(self->ble);
        list_push_back (ready_list, &node->elem);
        return;
    }
    
    ble_reenable_scan(self->ble);
    node->status = CONNECTED;
    node_insert (conn_list, node);

    return;
}

