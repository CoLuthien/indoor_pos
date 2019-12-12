#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "node_ctl.h" 
#include "list.h"
#include "ble.h"
#include "ble_filter.h"
#include "ble_misc.h"
#include "mavlink.h"
#include "comm.h"
#include "enum_states.h"

static struct list check_list = LIST_INITIALIZER(check_list);
static struct list unknown_list = LIST_INITIALIZER(unknown_list);
static struct list query_list = LIST_INITIALIZER (query_list);

static int ble_set_event_mask (int fd);

int ble_handle_disconn (struct ble_t* self, uint16_t handle);
int ble_handle_meta_evt (struct ble_t* self, evt_le_meta_event* evt);

static void ble_request_form(struct hci_request* form, uint16_t ocf, int clen, void* status, void* cparams);

static void ble_request_form(struct hci_request* form, uint16_t ocf, int clen, void* status, void* cparams)
{
    memset(form, 0, sizeof(struct hci_request));
    form->ogf = OGF_LE_CTL;
    form->ocf = ocf;
    form->cparam = cparams;
    form->clen = clen;
    form->rparam = status;
    form->rlen = 1;
}

int ble_handle_conn (struct ble_t* self, int timeout)
{
    if (list_empty (&self->ready_list))
    {
        return 0;// no need to do
    }

    struct node_basic* node = NULL;
    struct node_info* info = NULL;

    node = node_get_elem (list_front (&self->ready_list));
    info = node->info;
    ASSERT (node != NULL);
    ASSERT (node->status == READY);

    if (ble_try_connect (self->device, node->addr, &info->handle, timeout) < 0)
    {
        ble_cancel_connect (self->device, timeout);
        ble_reenable_scan (self->device);
        return -1;
    }

    list_remove (&node->elem);
    ble_reenable_scan (self->device);
    list_push_back (&self->conn_list, &node->elem);
    node->status = CONNECTED;
    return 0;
}


void ble_destroy (struct ble_t* ble)
{
    if (ble->scan)
    {
        ble_disable_scan (ble);
    }
    hci_close_dev(ble->device);
    free (ble);
    ble = NULL;
}

struct ble_t* ble_init()
{
    int dev = hci_open_dev(hci_get_route(NULL));
    struct ble_t* self = malloc(sizeof(struct ble_t));
    if (dev < 0)
    {
        goto fail;
    }

    if (hci_read_bd_addr(dev, &self->my_addr, 1000) < 0)
    {
        //can't identify self. something wrong.
        goto fail;
    }
    self->device = dev;
    self->pfd.fd = dev;
    self->pfd.events = POLLIN;
    list_init (&self->conn_list);
    list_init (&self->ready_list);
    ble_enable_scan (self->device);
    printf("ble init success %s is bdaddr\n", batostr(&self->my_addr));

    return self;

    fail:
        printf("ble init fail!\n");
        ble_destroy(self);
        return NULL;
}


static int ble_set_event_mask(int fd)
{
    int status;
    le_set_event_mask_cp event_mask;
    memset(&event_mask, 0, sizeof(event_mask));
    for (int i = 0; i < 8; i++)
        event_mask.mask[i] = 0xff;

    struct hci_request event_mask_rq;
    ble_request_form(&event_mask_rq, OCF_LE_SET_EVENT_MASK, LE_SET_EVENT_MASK_CP_SIZE
                            , &status, &event_mask);
    return hci_send_req(fd, &event_mask_rq, 1000);
}

int ble_get_query_pkt (struct ble_t* self, uint8_t buf [static MAVLINK_MAX_PACKET_LEN])
{
    struct list* target_list = &unknown_list;
    if (list_empty (target_list))
    {
        return -1;
    }
    size_t len;
    mavlink_message_t msg;

    struct list_elem* e = list_pop_front (target_list);
    struct node_basic* node = node_get_elem (e);
    list_push_back (&query_list, e);

    mavlink_msg_query_pack (1, 1, &msg, &self->my_addr, bluetooth, &node->addr);
    len = mavlink_msg_to_send_buffer (buf, &msg);

    return len;
}

int ble_get_node_report (struct ble_t* self, uint8_t buf[static MAVLINK_MAX_PACKET_LEN])
{
    struct list* target_list = &self->conn_list;
    if (list_empty (target_list))
        return -1;
    
    struct node_basic* node = NULL;
    struct node_info* info = NULL;
    uint8_t addrs [96];
    int8_t rssis [16];
    uint8_t* offset = addrs;
    struct list_elem* end = list_end (target_list);
    int len = list_size (target_list), i = 0;
    mavlink_message_t msg;

    for (struct list_elem* e = list_front (target_list);
         e != end;
         e = list_next (e))
    {
        if (i > 15)
            break;
        node = node_get_elem (e);
        info = node->info;
        bacpy (addrs + (i * 6), &node->addr);
        rssis[i] = info->rssi;        
        i++;
    }

    mavlink_msg_node_report_pack (1, 1, &msg, &self->my_addr, i, node->status, addrs, rssis);

    return mavlink_msg_to_send_buffer (buf, &msg);
}

int ble_handle_query (struct ble_t* self, mavlink_query_result_t* res)
{
    struct node_basic* node = NULL;
    struct node_info* info = NULL;
    bdaddr_t target;

    bacpy (&target, res->match_addr);
    node = node_find (target, &query_list);
    ASSERT (node != NULL);

    if (bacmp (res->addr, &self->my_addr) != 0)
    {
        list_remove (&node->elem);
        node_destroy (node);
        return -1;
    }

    if (res->is_usable == 0)
    {
        list_remove (&node->elem);
        node_destroy (node);
        return 0;
    }
    //node is usable!

    node->status = READY;
    node = (struct node_basic*) node_promote (node);

    info = node->info;
    info->real_x = res->x;
    info->real_y = res->y;
    info->real_z = res->z;

    list_remove (&node->elem);
    list_push_back (&self->ready_list, &node->elem);
    
    return 0;
}

int ble_process_mavlink (struct ble_t* self, mavlink_message_t* msg)
{
    struct node_basic* node = NULL;
    bdaddr_t target;
    mavlink_query_result_t res; 
    int ret = 0;
    switch (msg->msgid)
    {
    case MAVLINK_MSG_ID_query_result:
        mavlink_msg_query_result_decode (msg, &res);
        ret = ble_handle_query (self, &res);        
        break;
    default:
        break;
    }

    return ret;
}

void ble_read_rssis (struct ble_t* self, int timeout)
{
    struct node_basic* node = NULL;
    struct node_info* info = NULL;
    struct list* target_list = &self->conn_list;
    if (list_empty (target_list))
    {
        return;
    }

    struct list_elem* end = list_end (target_list);
    for (struct list_elem* e = list_front (target_list); 
        e != end; 
        e = list_next (e))
    {
        node = node_get_elem (e);
        info = node->info;
        ASSERT (node->status == CONNECTED);
        if (hci_read_rssi (self->device, info->handle, &info->rssi, timeout) < 0)
        {
            info->rssi = 127;
            if (errno == EIO)
            {
                ble_handle_disconn (self, info->handle);
            }
            continue;
        }
        clock_gettime (CLOCK_REALTIME, &node->update_at);
    }
}

int ble_handle_disconn (struct ble_t* self, uint16_t handle_off)
{
    if (list_empty (&self->conn_list))
    {
        return -1; //nothing to do 
    }

    struct list_elem* end = list_end (&self->conn_list);
    struct node_basic* node = NULL;
    struct node_info* info = NULL;
    for (struct list_elem* e = list_front (&self->conn_list);
         e != end;
         e = list_next (e))
    {
        node = node_get_elem (e);
        info = node->info;
        if (info->handle == handle_off)
        {
            list_remove (&node->elem);
            rm_dup_entry_byaddr (&check_list, node->addr);
            node_destroy (node);
            return 0;
        }
    }

    printf("can't reach, disconn handle not exist on list\n");
    exit(-1);
}

int ble_handle_meta_evt (struct ble_t* self, evt_le_meta_event* evt)
{
    void* offset = evt->data + 1;
    struct dup_elem* dup = NULL;
    struct node_basic* node = NULL;
    int num_report = 0;
    switch (evt->subevent)
    {
    case EVT_LE_ADVERTISING_REPORT:
        num_report = evt->data[0];
        for (int i = 0; i < num_report; i++)
        {
            le_advertising_info* info = (le_advertising_info*)
                            (offset);
            dup = find_dup_entry (&check_list, info->bdaddr);
            if (dup == NULL)
            {
                dup = create_dup_entry (info->bdaddr);
                list_push_front (&check_list, &dup->elem);

                node = node_create (info->bdaddr, FOUND);
                list_push_back (&unknown_list, &node->elem);
            }
            offset = (info->data + info->length + 2);
        }
        break;
    default:
        printf("unknown evt code %d\n", evt->subevent);
        break;
    }
}

int ble_process_hci_evt (struct ble_t* self, int timeout)
{
    uint8_t buf[HCI_MAX_EVENT_SIZE];
    bdaddr_t addr = {0x00,};
    hci_event_hdr* evt;
    short int old_evt = self->pfd.events;
    int ret = 0, len = 0, type = 0;
    
    self->pfd.events = POLLIN;

    ret = poll(&self->pfd, 1, timeout);
    if (ret <= 0 || !(self->pfd.revents & POLLIN))
    {
        return -1;        
    }

    len = read (self->device, buf, HCI_MAX_EVENT_SIZE);

    evt = (hci_event_hdr*) (buf + HCI_PKT_TYPE_LENGTH);
    type = evt->evt;

    printf("%x:code, %d \n", type, len);
    {
        evt_disconn_complete* disconn_evt; 
        evt_le_meta_event* meta_evt; 
        switch (type)
        {
        case EVT_DISCONN_COMPLETE:    
            disconn_evt = (evt_disconn_complete*) 
                            (buf + HCI_PKT_TYPE_LENGTH + HCI_EVENT_HDR_SIZE);
            ret = ble_handle_disconn (self, disconn_evt->handle);
            printf("disconn occur\n");
            break;
        case EVT_LE_META_EVENT:
            meta_evt = (evt_le_meta_event*)
                        (buf + HCI_EVENT_HDR_SIZE + HCI_PKT_TYPE_LENGTH);
            ret = ble_handle_meta_evt (self, meta_evt);
            break;
        case EVT_CMD_COMPLETE:

        default:
            ret = -1;// unknown pkt error
            break;
        }
    }
    

    return 0;
}


void ble_print_dup_filter (struct ble_t* self)
{
    if (list_empty (&check_list))
        return;
    
    struct list_elem* end = list_end (&check_list);
    struct list_elem* e = NULL;
    struct dup_elem* cur;

    for (e = list_front (&check_list);
         e != end;
         e = list_next (e))
    {
        cur = list_entry (e, struct dup_elem, elem);
        printf("%s\t", batostr(&cur->addr));
    }
    printf("\n\n");
}