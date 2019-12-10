#ifndef _BLE_MISC_H
#define _BLE_MISC_H

#define HCI_PKT_TYPE_LENGTH 1

#include <stdint.h>
#include <bluetooth/bluetooth.h>


int ble_enable_scan (int device);
int ble_reenable_scan (int device);
int ble_disable_scan (int device);

int ble_try_connect (int device, bdaddr_t addr, uint16_t* dst, int timeout);
int ble_end_connection (int device, uint16_t handle, uint8_t reason, int timeout);
int ble_cancel_connect (int device, int timeout);

#endif