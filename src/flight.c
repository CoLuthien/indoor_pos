#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "flight.h"
#include "mavlink.h"
#include "enum_states.h"

struct flight_t* flt_init (struct ble_t* ble, struct position_t* pos)
{
    struct flight_t* self = malloc (sizeof (struct flight_t));
    self->pos = pos;
    self->ble = ble;
    self->sys_status = SYS_INIT;

    list_init (&self->record);
}

void flt_destroy (struct flight_t* target)
{
    if (list_empty (&target->record))
    {
        free (target);
        target = NULL;
    }

    while (!list_empty (&target->record)) 
    {
        struct list_elem* e = list_pop_front(&target->record);
        struct point* p = list_entry (e, struct point, elem);
        free (p);
    }

    free (target);
}

int flt_request_record (struct flight_t* self, uint8_t buf [static MAVLINK_MAX_PACKET_LEN])
{
    mavlink_message_t msg;
    mavlink_msg_path_request_pack (1, 1, &msg, &self->ble->my_addr, 10, 100);
    return mavlink_msg_to_send_buffer (buf, &msg);     
}

bool flt_fetch_loc (struct flight_t* self, struct point* loc)
{
    struct list* target_list = &self->record;
    if (list_empty (target_list))
    {
        return false;
    }

    struct point* p = (struct point*) list_entry (list_pop_front (target_list), struct point, elem);
    memcpy (loc, p, sizeof (struct point));
    free (loc);
    return true;
}

void flt_record_loc (struct flight_t* self)
{
    struct point* p = malloc (sizeof (struct point));
    struct position_t* pos = self->pos;

    p->x = pos->cur_x;
    p->y = pos->cur_y;
    p->z = pos->cur_z;
    clock_gettme (CLOCK_REALTIME, &p->at);

    int len = list_size (&self->record);
    if (len > 100)
    {
        struct list_elem* e = list_pop_back (&self->record);
        struct point* removed = list_entry (e, struct point, elem);
        free(removed);
    }

    list_push_front (&self->record, &p->elem);
}

void flt_make_path (struct flight_t* self)
{
    struct point next_point; 
    struct point curr_point;
    struct position_t* pos = self->pos;
    curr_point.x = pos->cur_x;
    curr_point.y = pos->cur_y;
    curr_point.z = pos->cur_z;
    
    float diff[3];

    if (!flt_fetch_loc (self, &next_point))
        {
            return;
        }
        diff[0] = -(curr_point.x - next_point.x);
        diff[1] = -(curr_point.y - next_point.y);
        diff[2] = -(curr_point.z - next_point.z);

        if (diff[0] < 0)
        {
            printf("left %d", (int) (diff[0] * 100));
        }
        else 
        {
            printf("right %d", (int) (diff[0] * 100));
        }


        if (diff[1] < 0)
        {
            printf("back %d", (int) (diff[1] * 100));
        }
        else 
        {
            printf("forward %d", (int) (diff[1] * 100));
        }


        if (diff[2] < 0)
        {
            printf("down %d", (int) (diff[2] * 100));
        }
        else 
        {
            printf("up %d", (int) (diff[2] * 100));
        }
}

void flt_handle_mavlink (struct flight_t* self, mavlink_message_t* msg)
{
    mavlink_path_response_t path;
    mavlink_msg_path_response_decode (msg, &path);

    struct point p;
    p.x = path.x;
    p.y = path.y;
    p.z = path.z;


}


