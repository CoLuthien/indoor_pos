#ifndef _FLIGHT_H
#define _FLIGHT_H

#include <stdint.h>
#include <time.h>

#include "list.h"
#include "comm.h"
#include "ble.h"
#include "position.h"

struct point 
{
    struct list_elem elem;
    struct timespec at;
    float x, y, z;
};

struct flight_t
{
    struct ble_t* ble;
    struct position_t* pos;
    uint8_t sys_status;
    struct timespec start_at, request_time;

    
    struct list record;
    bool is_full;
};

struct flight_t* flt_init ();
void flt_destroy (struct flight_t* target);

int flt_request_record (struct flight_t* self, uint8_t buf [static MAVLINK_MAX_PACKET_LEN]);
void flt_handle_mavlink (struct flight_t* self, mavlink_message_t* msg);

bool flt_fetch_loc (struct flight_t* self, struct point* loc);
void flt_record_loc (struct flight_t* self);

void flt_make_path (struct flight_t* self);






#endif