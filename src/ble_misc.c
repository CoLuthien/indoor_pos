#include "ble_misc.h"

#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <stdbool.h>
#include <poll.h>

int ble_cancel_connect (int device, int timeout)
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

    return hci_send_req (device, &rq, timeout);
}

int ble_try_connect (int device, bdaddr_t addr, uint16_t* dst, int timeout)
{
    uint16_t handle = 1;
    int ret = hci_le_create_conn(device, 0x0020, 0x0020,
        0x00, 0x00, addr, 0x00, 0x0010, 0x0020, 0x0010,
        0x100, 0x00, 0x10, &handle, timeout);
    if (ret < 0)
    {
        return ret;
    }

    *dst = handle;
    return 0;
}

int ble_end_connection (int device, uint16_t handle, uint8_t reason, int timeout)
{
    return hci_disconnect (device, handle, reason, timeout);
}

int ble_reenable_scan (int device)
{
 
    int ret = hci_le_set_scan_enable(device, 0x01, 0x01, 1000);// we will handle duplicates
    if (ret < 0)
    {
        return -1;
    }
    return 0;
}

int ble_enable_scan(int device)
{
    /* 
    ToDo:
        scan parameter change to dynamic
    */
    int status = 0, ret = 0;
    int fd = device;

    
    ret = hci_le_set_scan_parameters(fd, 0x00, 0x0010, 0x0010, 0x00, 0x00, 1000);

    if (ret != 0)
    {
        printf("Failed to set scan parameters. Error code is %d\n", ret);
        goto fail;
    }

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
    hci_filter_set_event(EVT_DISCONN_COMPLETE, &nf);

    if(setsockopt(fd, SOL_HCI, HCI_FILTER, &nf, sizeof(nf)) < 0)
    {
        printf("Failed to set socket option.");
        goto fail;
    }

    printf("Succeed to enable scan!\n");
    return 0;

    fail:
        return -1;
}

inline int ble_disable_scan (int device)
{
    if (hci_le_set_scan_enable(device, 0x00, 0x00, 1000) < 0)
    {
        return -1;
    }
    
    return 0;
}