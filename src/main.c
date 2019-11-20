#include <stdio.h>
#include "ble.h"
#include "position.h"
#include "comm.h"
#include "mavlink.h"


struct ble_t* ble = NULL;
struct comm_t* com = NULL;
struct position_t* pos = NULL;



int init_main (const char* serv_addr, const char* serv_port)
{//todo
    ble = ble_init ();
    com = comm_init (serv_addr, serv_port);
    pos = pos_init (ble, com);
}

void send_status_report()
{
    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint16_t len;
    float tmp[2];
    tmp[0] = pos->cur_x, tmp[1] = pos->cur_y;
    mavlink_msg_stat_report_pack (
        0,
        0,
        &msg,
        ble->my_addr.b,
        pos->status,
        pos->active_list.len,
        tmp
    );

    len = mavlink_msg_to_send_buffer (buf, &msg);
    comm_write (com, buf, len);
}

void send_heartbeat()
{
    mavlink_message_t msg;
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    uint16_t len;
    mavlink_msg_heartbeat_pack (
        0,
        0,
        &msg,
        ble->my_addr.b,
        pos->status,
        0
    );
    len = mavlink_msg_to_send_buffer (buf, &msg);
    comm_write (com, buf, len);
}

int prepare_flight ()
{
    if (ble_enable_scan (ble) < 0)
    {
        // what should we do..
        return -1;
    }
    pos->status = ONLY_BLE;

}


int main()
{

    return 0;
}