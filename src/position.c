#include "position.h"
#include "mavlink.h"
#include <stdio.h>
#include <stdlib.h>


#define MAX_PKT_LEN 8

static struct node_list unknown_nodes;

static int pos_process_query_result (struct position_t* self, mavlink_message_t* msg);
static int pos_do_query (struct position_t* self);
static void pos_query_to_server (struct position_t* self, bdaddr_t addr);


struct position_t* pos_init ()
{
    node_list_init (&unknown_nodes);
}

void pos_scan_perimeter (struct position_t* self, int timeout)
{
    bdaddr_t addr_found;
    
    if (ble_get_scan_result (self->ble, &addr_found, timeout) > 0)
    {
        pos_query_to_server (self, addr_found);
    }
}

static void pos_query_to_server (struct position_t* self, bdaddr_t addr)
{
    struct node_basic* node = node_find (addr, &unknown_nodes);
    if (NULL == node)
    {
        node = node_create (addr, FOUND);
        node_insert (&unknown_nodes, node);
    }
    if (unknown_nodes.len >= 8 || 0) // if query criteria mets, query to server
    {
        pos_do_query (self);
    }
}

static int pos_do_query (struct position_t* self)
{
    uint8_t buf[48];// sizeof (struct target_pkt)
    uint8_t msg_buf[MAVLINK_MAX_PACKET_LEN];
    struct list* list = &unknown_nodes.head;
    struct list_elem* end = list_end(&unknown_nodes.head);
    struct node_basic* cur = NULL;
    int cnt = 0;
    for (struct list_elem* e = list_front(list);
         e != end;
         e = list_next(e))
    {
        if (cnt > 7)
            break;
        cur = node_get_elem (e);
        bacpy (buf + cnt * 6, &cur->addr);
        cnt++;
    }
    mavlink_message_t msg;
    mavlink_msg_query_pack (0, 0, 
        &msg, &self->ble->my_addr, 
        self->status, cnt, buf);
    int len = mavlink_msg_to_send_buffer(msg_buf, &msg);
    return comm_write (self->com, msg_buf, len);
}

int pos_process_packet (struct position_t* self, int timeout)
{
    struct comm_t* com = self->com;
    uint8_t msg_buf[MAVLINK_MAX_PACKET_LEN] = {0,};
    mavlink_message_t msg;
    mavlink_status_t stat;

    int len = comm_read(com, msg_buf, MAVLINK_MAX_PACKET_LEN, timeout);
    if (len < 0)
        return -2;// nothing to do.. for now..
    else if (len == 0)
        return -1; // nothing arrived yet

    for (int i = 0; i < len; i++)
    {
        if (mavlink_parse_char(MAVLINK_COMM_0, msg_buf[i], &msg, &stat))
        {
            switch (msg.msgid)
            {
            case MAVLINK_MSG_ID_heartbeat:
                break;
            case MAVLINK_MSG_ID_query:
                break;// will not sent by server
            case MAVLINK_MSG_ID_query_result:

                pos_process_query_result(self, &msg);                            
                break;
            case MAVLINK_MSG_ID_command:
                break;
            default:
                break;
            }
        }
    }

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