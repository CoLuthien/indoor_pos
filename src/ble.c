#include "ble.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int ble_cancel_connect (struct ble_t* self); 
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

    return self;

    fail:
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

static int ble_parse_scan_result(uint8_t* buf, size_t len, bdaddr_t* dest)// temporary implemetation
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

int ble_start_scan(struct ble_t* self)
{
    /* 
    ToDo:
        scan parameter change to dynamic
    */
    int status = 0, ret = 0;
    int fd = self->device;

    ret = hci_le_set_scan_parameters(fd, 0x01, 0x00a0, 0x00a0, 0x00, 0x00, 1000);

    if (ret != 0)
    {
        printf("Failed to set scan parameters. Error code is %d\n", ret);
        goto fail;
    }

    ret = ble_set_event_mask(fd); 

    if (ret != 0)
    {
        printf("Failed to set event mask. Error code is %d\n", ret);
        goto fail;
    }

    ret = hci_le_set_scan_enable(fd, 0x01, 0x01, 1000);
    if (ret < 0)
    {
        printf("failed to enable scan\n");
        goto fail;
    }


    struct hci_filter nf;
    hci_filter_clear(&nf);
    hci_filter_set_ptype(HCI_EVENT_PKT, &nf);
    hci_filter_set_event(EVT_LE_META_EVENT, &nf);

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
inline int ble_stop_scan(struct ble_t* self)
{
    
    if (hci_le_set_scan_enable(self->device, 0x00, 0x00, 1000) > 0)
    {
        self->scan = false;
        return 0;
    }
    return -1;
}

// error -1, no response 0, success > 0
int ble_get_scan_result (struct ble_t* self, bdaddr_t* dest, int timeout)
{
    uint8_t buf[HCI_MAX_EVENT_SIZE];
    short int old_evt = self->pfd.events;
    int ret = 0, len = 0;
    
    self->pfd.events = POLLIN;

    ret = poll(&self->pfd, 1, timeout);
    if (self->pfd.revents & POLLIN)
    {
        len = read(self->device, buf, HCI_MAX_EVENT_SIZE);
        if (len >= HCI_EVENT_HDR_SIZE)
        {
            ble_parse_scan_result(buf, len, dest);
            ret = len;
        }
     }
   
    return ret;
}

static int ble_cancel_connect (struct ble_t* self, int timeout)
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
    uint16_t handle = 0;
    int ret = hci_le_create_conn(self->device, 0x0030, 0x0030,
        0x00, 0x00, addr, 0x00, 0x0010, 0x0020, 0x0010,
        0x100, 0x00, 0x10, &handle, timeout);
    
    if (ret < 0)
    {
        //something happen.
        return ble_cancel_connect(self, timeout);// need dynamic!
    }

    *dst = handle;
    return 0;
}

int ble_read_rssi (struct ble_t* self, uint16_t handle, int8_t* dest, int timeout)
{
    return hci_read_rssi (self->device, handle, &dest, timeout);
}
