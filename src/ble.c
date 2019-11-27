#include "ble.h"
#include "list.h"
#include "ble_filter.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>



static struct list check_list;
static int ble_set_event_mask (int fd);
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

    printf("ble init success %s is bdaddr\n", batostr(&self->my_addr));
    list_init (&check_list);

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


/*
    parse le_meta_evt, specifically EVT_LE_ADVERTISING REPORT
    return 0 when packet exist,
           -1 when packet is not the type
*/
static inline int ble_parse_scan_result(uint8_t* buf, size_t len, bdaddr_t* dest)// temporary implemetation
{
    evt_le_meta_event* meta_event;
	le_advertising_info* info;
    void* offset = NULL;

    meta_event = (evt_le_meta_event*) (buf + HCI_EVENT_HDR_SIZE + 1);
    if (meta_event->subevent == EVT_LE_ADVERTISING_REPORT)
    {
        offset = meta_event->data + 1;
        info = (le_advertising_info*) offset;
        bacpy (dest, &info->bdaddr);
        return 0;
    }
    return -1;
}

int ble_enable_scan(struct ble_t* self)
{
    /* 
    ToDo:
        scan parameter change to dynamic
    */
    int status = 0, ret = 0;
    int fd = self->device;

    
    ret = hci_le_set_scan_parameters(fd, 0x00, 0x0010, 0x0010, 0x00, 0x00, 1000);

    if (ret != 0)
    {
        printf("Failed to set scan parameters. Error code is %d\n", ret);
        goto fail;
    }
/*
    ret = ble_set_event_mask(fd); 

    if (ret != 0)
    {
        printf("Failed to set event mask. Error code is %d\n", ret);
        goto fail;
    }
*/

    ret = hci_le_set_scan_enable(fd, 0x01, 0x01, 1000);// we will handle duplicates
    if (ret < 0)
    {
        printf("failed to enable scan\n");
        goto fail;
    }


    struct hci_filter nf;
    hci_filter_clear(&nf);
    hci_filter_set_ptype(HCI_EVENT_PKT, &nf);
    hci_filter_set_event(EVT_LE_META_EVENT, &nf);
    hci_filter_set_event(EVT_CMD_COMPLETE, &nf);
    hci_filter_set_event(EVT_CMD_STATUS, &nf);

    if(setsockopt(fd, SOL_HCI, HCI_FILTER, &nf, sizeof(nf)) < 0)
    {
        printf("Failed to set socket option.");
        goto fail;
    }

    printf("Succeed to enable scan!\n");
    self->scan = true;
    return 0;

    fail:
        self->scan = false;
        return -1;
}

inline int ble_disable_scan (struct ble_t* self)
{
    if (hci_le_set_scan_enable(self->device, 0x00, 0x00, 1000) < 0)
    {
        return -1;
    }
    reset_dup_entry (&check_list);
    self->scan = false;
    return 0;
}

void ble_rm_addr (struct ble_t* self, bdaddr_t addr)
{
    rm_dup_entry_byaddr (&check_list, addr);
}
//return on error -1,  success  0
int ble_get_scan_result (struct ble_t* self, bdaddr_t* dest, int timeout)
{
    if (!self->scan)
    {
        return -1;
    }
    uint8_t buf[HCI_MAX_EVENT_SIZE];
    bdaddr_t addr = {0x00,};
    short int old_evt = self->pfd.events;
    int ret = 0, len = 0;
    struct dup_elem* dup = NULL;
    
    self->pfd.events = POLLIN;

    ret = poll(&self->pfd, 1, timeout);
    if (ret <= 0 || !(self->pfd.revents & POLLIN) )
    {
        return -1;        
    }

    len = read (self->pfd.fd, buf, HCI_MAX_EVENT_SIZE);
    if (ble_parse_scan_result (buf, len, &addr) < 0)
    {
        return -1;
    }

    //check duplication
    dup = find_dup_entry (&check_list, addr);
    if (NULL == dup) 
    {
        dup = create_dup_entry (addr);
        insert_dup_entry (&check_list, dup);
        bacpy (dest, &addr);
        return 0;
    }

    return -1;
}

int ble_cancel_connect (struct ble_t* self, int timeout)
{
    int ret = 0;
    struct hci_request rq = {0, };
    evt_le_connection_complete evt = {0, };
    rq.ogf = OGF_LE_CTL;
    rq.ocf = OCF_LE_CREATE_CONN_CANCEL;
    rq.event = EVT_LE_CONN_COMPLETE;
    rq.cparam = NULL;
    rq.clen = 0;
    rq.rparam = &evt;
    rq.rlen = EVT_LE_CONN_COMPLETE_SIZE;

    return hci_send_req (self->device, &rq, timeout);
}

int ble_try_connect (struct ble_t* self, bdaddr_t addr, uint16_t* dst, int timeout)
{
    uint16_t handle = 1;
    int ret = hci_le_create_conn(self->device, 0x0120, 0x0120,
        0x00, 0x00, addr, 0x00, 0x0010, 0x0020, 0x0010,
        0x100, 0x00, 0x10, &handle, timeout);
    if (ret < 0)
    {
        return ret;
    }

    *dst = handle;
    return ret;
}

int ble_read_rssi (struct ble_t* self, uint16_t device_handle, int8_t* dest, int timeout)
{
    return hci_read_rssi (self->device, device_handle, dest, timeout);
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

int ble_end_connection (struct ble_t* self, uint16_t handle, uint8_t reason, int timeout)
{
    return hci_disconnect (self->device, handle, reason, timeout);
}


