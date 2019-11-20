#include "node_ctl.h"
#include "position.h"
#include "mavlink.h"
#include <stdio.h>
#include <stdlib.h>

#define QUERY_THRESHOLD 8
#define MAX_PKT_LEN 8

static struct node_list unknown_nodes;
static struct node_list queried_nodes;
static struct node_list dup_filter;//duplication filter purpose

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
    node_list_init (&self->active_list);
    node_list_init (&unknown_nodes);
    node_list_init (&queried_nodes);
    node_list_init (&dup_filter);

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
    // we need to filter out duplicates
    struct node_basic* node = node_find (addr, &dup_filter);
    if (node == NULL)
    {// very first found
        node = node_create (addr, FILTER_USE);
        node_insert (&dup_filter, node);
        
        node = NULL;// it is in list. we don't care

        node = node_create (addr, FOUND);
        node_insert (&unknown_nodes, node);
    }
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
    struct list* cand_list = &self->active_list.head;
    struct list_elem* e = NULL;
    struct list_elem* end = list_back (cand_list);
    struct node_basic* cur = NULL;
    struct node_info* info = NULL;

    struct ble_t* ble = self->ble;
    float est_x, est_y;
    int list_len = self->active_list.len;
    int ret = 0;

    int time_to_process = timeout / list_len;
        
    for (e = list_front (cand_list); e != end; e = list_next(e))
    {
        cur = node_get_elem (e);
        info = cur->info;
        if (cur->status == CONNECTED)
        {
            ret = hci_read_rssi(ble->device, info->handle, &info->rssi, time_to_process);
        }
        else
        {
            ret = ble_try_connect (ble, cur->addr, &info->handle, time_to_process);
        }

        if (ret < 0)
        {
            cur->status = ERROR;
            continue;
        }
    }

    self->cur_x = est_x;
    self->cur_y = est_y;

    return 0;        
}

int pos_process_query_result (struct position_t* self, mavlink_message_t* msg)
{
    mavlink_query_result_t res;
    struct node_basic* node = NULL;
    struct node_info* info = NULL;
    bdaddr_t matched;

    mavlink_msg_query_result_decode (msg, &res);

    bacpy (&matched, res.match_addr);
    float x = res.x, y = res.y;

    node = node_find (matched, &unknown_nodes);
    if (NULL == node)
    {
        return -1;// drone moves fast, or error
    }

    node_promote (node);

    node->status = READY;
    info = node->info;

    info->real_x = x, info->real_y = y;

    node_remove_frm_list (&unknown_nodes, node);
    node_insert (&self->ready_list, node);

    return 0;
}
