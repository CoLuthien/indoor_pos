#include "node_ctl.h"
#include "position.h"
#include "mavlink.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct position_t* pos_init (struct ble_t* ble, struct comm_t* com)
{
    if (NULL == ble || NULL == com)
    {
        goto fail;
    }
    struct position_t* self = malloc (sizeof (struct position_t));

    self->ble = ble; 
    self->com = com;
    ASSERT (ble != NULL && com != NULL);


    self->status = INIT;
    self->pos_valid = false;
    self->cur_x = self->cur_y = 200.0f;

    return self;

    fail:
        printf("init position failed!!\n");
        return NULL;
}

int pos_get_stat_report (struct position_t* self, uint8_t buf[static MAVLINK_MAX_PACKET_LEN])
{
    size_t len;
    mavlink_message_t msg;
    float pos[3];
    pos[0] = self->cur_x; pos[1] = self->cur_y; pos[2] = self->cur_z;

    mavlink_msg_pos_report_pack (1, 1, &msg, &self->ble->my_addr,
                 self->status, self->est_at.tv_sec, self->est_at.tv_nsec, pos);
    len = mavlink_msg_to_send_buffer (buf, &msg);
    return len;
}

int pos_estimate_position (struct position_t* self, int timeout)
{
    struct list* conn_list = &self->ble->conn_list;
    if (list_empty (conn_list))
    {
        return -1;
    }

    struct node_basic* node = NULL;
    struct node_info* info = NULL;
    struct list_elem* end = list_end (conn_list);
    float weight_sum = 0.0f, norm_weight_sum = 0.0f;
    struct list temp_list;
    list_init (&temp_list);

    for (struct list_elem* e = list_front (conn_list); e != end;)
    {
        // filter invalid rssi nodes
        node = node_get_elem (e);
        info = node->info;
        if (info->rssi == 127)
        {
            e = list_remove (e);
            list_push_back (&temp_list, &node->elem);
            continue;
        }

        info->weight = sqrtf (powf(10.0f, ((float) info->rssi) / 10.0f)
                             );
        weight_sum += info->weight;        
        e = list_next (e);
    }

    if (list_empty (conn_list))
        goto recover;


    end = list_end (conn_list);
    int len = list_size (conn_list);
    for (struct list_elem* e = list_front (conn_list); e != end; e = list_next(e))
    {
        node = node_get_elem (e);
        info = node->info;
        info->weight = info->weight / weight_sum; // normalize weight

        info->weight = (info->weight * powf ((float) len, 2.0 * info->weight)); //improved weight
        norm_weight_sum += info->weight;
    }

    float est_x = 0.0f, est_y = 0.0f;
    
    for (struct list_elem* e = list_front (conn_list); e != end; e = list_next(e))
    {
        node = node_get_elem (e);
        info = node->info;

        info->weight = info->weight / norm_weight_sum; // final weight
        // now calc est pos
        est_x += info->weight * info->real_x;
        est_y += info->weight * info->real_y;
    }

    self->cur_x = est_x;
    self->cur_y = est_y;
    clock_gettime(CLOCK_REALTIME, &self->est_at);

    recover:
    if (!list_empty (&temp_list))
    {
        end = list_end (&temp_list);
        for (struct list_elem* e = list_front (&temp_list); e != end;)
        {
            node = node_get_elem (e);
            e = list_remove (e);

            list_push_back (conn_list, &node->elem);
        }        
    }

    node = node_get_elem (list_front (conn_list));
    info = node->info;
    
    return 0;
}

void pos_print_nodes (struct position_t* self, struct node_list* target)
{
    struct list* target_list = &target->head;
    if (list_empty (target_list))
        return;
    
    struct list_elem* end = list_end (target_list);
    struct list_elem* e = NULL;
    struct node_basic* cur;
    int cnt = 0;
    for (e = list_front (target_list);
         e != end;
         e = list_next (e))
    {
        cur = list_entry (e, struct node_basic, elem);
        printf("%s\t", batostr(&cur->addr));
    }
    printf("\n\n");
}

