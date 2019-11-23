#include "node_ctl.h"
#include "ble.h"
#include "comm.h"
#include "packet.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct position_t
{
    struct ble_t* ble;
    struct comm_t* com;
    struct node_list ready_list, active_list;
    uint8_t status;
    
    bool pos_valid ;
    float cur_x, cur_y;
};

struct position_t* pos_init (struct ble_t* ble, struct comm_t* com);

void pos_scan_perimeter (struct position_t* self, int timeout);
int pos_estimate_position (struct position_t* self, int timeout);

int pos_query_nodes (struct position_t* self, int timeout);



//debuggin purpose

void pos_print_nodes (struct position_t* self, struct node_list* target);
