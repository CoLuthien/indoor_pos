#ifndef _BLE_H
#define _BLE_H

#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <stdbool.h>
#include <poll.h>

struct ble_t
{
    bdaddr_t my_addr;
    struct pollfd pfd;
    int device;
    bool scan;
    bool filter_clear;
};

struct ble_t* ble_init ();
void ble_destroy (struct ble_t* ble);

int ble_enable_scan (struct ble_t* self);
int ble_reenable_scan (struct ble_t* self);
int ble_disable_scan (struct ble_t* self);

int ble_get_scan_result (struct ble_t* self, bdaddr_t* dest, int timeout);

int ble_try_connect (struct ble_t* self, bdaddr_t addr, uint16_t* dst, int timeout);
int ble_end_connection (struct ble_t* self, uint16_t handle, uint8_t reason, int timeout);
int ble_cancel_connect (struct ble_t* self, int timeout); 

int ble_read_rssi (struct ble_t* self, uint16_t device_handle, int8_t* dest, int timeout);
void ble_rm_addr (struct ble_t* self, bdaddr_t addr);

void ble_print_dup_filter (struct ble_t* self);





#endif