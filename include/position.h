#ifndef _POSITION_H
#define _POSITION_H
#include "node_ctl.h"
#include "ble.h"
#include "comm.h"
#include "enum_states.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "time.h"


struct position_t
{
    struct ble_t* ble;
    struct comm_t* com;
    uint8_t status;
    
    bool pos_valid;
    float cur_x, cur_y, cur_z;
    struct timespec est_at;
};

struct position_t* pos_init (struct ble_t* ble, struct comm_t* com);

int pos_estimate_position (struct position_t* self, int timeout);

int pos_get_stat_report (struct position_t* self, uint8_t buf [static MAVLINK_MAX_PACKET_LEN]);


//debuggin purpose
void pos_print_nodes (struct position_t* self, struct node_list* target);

#endif