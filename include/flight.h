#ifndef _FLIGHT_H
#define _FLIGHT_H

#include <stdint.h>
#include <time.h>

#include "list.h"
#include "comm.h"

struct point 
{
    struct list_elem elem;
    uint64_t idx;
    float x, y, z;
};

struct flight_t
{
    uint8_t sys_status;
    uint16_t reserve_count; // how much entry of path?
    uint64_t time_measure_start;

    struct comm_t* com;
    
    struct list prev_path;
    struct list recvd_prev_path;
};

int request_prev_path (struct flight_t* self);
int 




#endif