#include "node_ctl.h"
#include "position.h"
#include "mavlink.h"
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

void pos_scan_perimeter (struct position_t* self, int timeout)
{
    bdaddr_t addr_found = {0x00, };
    if (ble_get_scan_result (self->ble, &addr_found, timeout) < 0)
    {
        return;
    }
    //ok something outside.
    pos_process_scan_result (self, addr_found);
}

int pos_estimate_position (struct position_t* self, int timeout)
{
    struct node_basic* node = NULL;
    struct node_info* info = NULL;
    struct list* conn_list = &self->conn_list.head;

    if (list_empty(conn_list))
    {
        //ToDo: handle 
        return -1;
    }

    struct list_elem* end = list_end (conn_list);

    for (struct list_elem* e = list_front (conn_list); e != end; e = list_next(e))
    {
        node = node_get_elem (e);
        info = node->info;
        if (!info->rssi_valid)
            continue;
        
    }

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

int pos_query_nodes (struct position_t* self, int timeout)
{
    struct node_basic* node = NULL;
    struct list* unknown_list = &unknown_nodes.head;
    mavlink_message_t msg;
    uint16_t len = 0;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];

    if (list_empty (unknown_list))
    {
        return -1;
    }
    
    struct list* queried_list = &queried_nodes.head;
    uint8_t addrs[6] = {0,}; 
    struct list_elem* e  = list_front (unknown_list);
    node = node_get_elem (e);

    node_remove_frm_list (&unknown_nodes, node);
    node_insert (&queried_nodes, node);
        
    bacpy (addrs, &node->addr);

    mavlink_msg_query_pack (1, 1, &msg, &self->ble->my_addr, self->status, 1, addrs);
    len = mavlink_msg_to_send_buffer (buf, &msg);

    return comm_append_write (self->com, buf, len);
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
        return -1;
    }

    bacpy (&target_addr, res.match_addr);

    node = node_find (target_addr, &queried_nodes);
    if (NULL == node)
    {
        return -1;
    }
    
    if (res.is_usable == 0)
    {
        node_remove_frm_list (&queried_nodes, node);
        node_destroy (node);
        return 0;
    }

    node->status = READY;
    node_promote(node);

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
    if (len < 0)
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

    if (self->conn_list.len >= 16)
    {
        return;
    }

    node = node_get_elem (list_pop_front (ready_list));
    info = node->info;

    if (ble_try_connect (self->ble, node->addr, &info->handle, timeout) <0)
    {
        ble_cancel_connect (self->ble, timeout);
        node_insert (ready_list, node);
        return;
    }

    node->status = CONNECTED;
    node_insert (conn_list, node);
    return;
}


void pos_prepare_estimation (struct position_t* self, int timeout)
{
    struct node_basic* node = NULL;
    struct node_info* info = NULL;
    struct list* target_list = &self->conn_list.head;
    if (list_empty (target_list))
    {
        return;
    }

    struct list_elem* end = list_end (target_list);

    for (struct list_elem* e = list_front (target_list); e != end; e = list_next (e))
    {
        node = node_get_elem (e);
        info = node->info;
        if (ble_read_rssi (self->ble, info->handle, &info->rssi, timeout) < 0)
        {
            info->rssi = 127;
            info->rssi_valid = false;
            continue;
        }
        info->rssi_valid = true;
    }
}
