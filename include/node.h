#ifndef _NODE_H
#define _NODE_H

#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <bluetooth/bluetooth.h>

#include "list.h"


enum node_status
{
    REMOVE = 0,
    FOUND, // found on scan, not sure to use
    READY, // DB confirm to use
    CONNECTED,
    ERROR,
    FILTER_USE
};

struct node_basic
{
    bdaddr_t addr;
    uint8_t status;
    struct list_elem elem;
    struct timespec update_at;
    char info[0];
};

struct node_info 
{
    uint16_t handle;
    int8_t rssi;
    float real_x, real_y, real_z;
    float weight, dist;
    float est_x, est_y, est_z;
};

#endif