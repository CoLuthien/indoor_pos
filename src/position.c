#include "node_ctl.h"
#include "position.h"
#include "mavlink.h"
#include <stdio.h>
#include <stdlib.h>

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
    node_list_init (&self->active_list);
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
    struct list* cand_list = &self->active_list.head;
    struct list_elem* e = NULL;
    struct list_elem* end = list_end (cand_list);
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

void pos_print_nodes (struct position_t* self, struct node_list* target)
{
    struct list* target_list = &target->head;
    if (list_empty (target_list))
        return NULL;
    
    struct list_elem* end = list_end (target_list);
    struct list_elem* e = NULL;
    struct node_basic* cur;

    for (e = list_front (&target_list);
         e != end;
         e = list_next (e))
    {
        cur = list_entry (e, struct node_basic, elem);
        printf("%s\t", batostr(&cur->addr));
    }
    printf("\n\n");
}

