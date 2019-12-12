#ifndef _BLE_H
#define _BLE_H

#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <stdbool.h>
#include <poll.h>

#include "list.h"
#include "node_ctl.h"
#include "mavlink.h"

struct ble_t
{
    bdaddr_t my_addr;
    struct pollfd pfd;
    struct list conn_list, ready_list;
    int device;
    bool scan;
    bool filter_clear;
};

//ble control interface
struct ble_t* ble_init ();
void ble_destroy (struct ble_t* ble);
void ble_read_rssis (struct ble_t* self, int timeout);
int ble_handle_conn (struct ble_t* self, int timeout);
int ble_process_hci_evt (struct ble_t* self, int timeout);

//ble comm with server interface
int ble_get_query_pkt (struct ble_t* self, uint8_t buf [static MAVLINK_MAX_PACKET_LEN]);
int ble_process_mavlink (struct ble_t* self, mavlink_message_t* msg);
int ble_get_node_report (struct ble_t* self, uint8_t buf [static MAVLINK_MAX_PACKET_LEN]);



void ble_print_dup_filter (struct ble_t* self);





#endif