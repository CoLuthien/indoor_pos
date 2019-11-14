#include "node_ctl.h"
#include "ble.h"
#include "comm.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct position_t
{
    struct ble_t* ble;
    struct comm_t* com;
    struct node_list unknown_list, ready_list, active_list;
    uint8_t status;
    
    bool pos_valid;
    float cur_x, cur_y;
};

int pos_scan_perimeter(struct position_t* self);
int pos_query_to_server(struct position_t* self);
int pos_parse_query(struct position_t* self, uint8_t* buf, size_t len);
int pos_process_query(struct position_t* self);

