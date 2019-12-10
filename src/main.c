#include <stdio.h>
#include <time.h>
#include "ble.h"
#include "position.h"
#include "comm.h"
#include "mavlink.h"


struct ble_t* ble = NULL;
struct comm_t* com = NULL;
struct position_t* pos = NULL;



int init_main (const char* serv_addr, const char* serv_port)
{//todo
    com = comm_init (serv_addr, serv_port);
    ASSERT (com != NULL);

    ble = ble_init ();
    pos = pos_init (ble, com);

    return 0;
}

void report_status()
{
    struct timespec ts;

}

int exec_query ()
{
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];
    int len = ble_get_query_pkt (ble, buf);
    if (len < 0 )
        return -1;

    return comm_append_write (com, buf, len);
}

int receive_pkt ()
{
    uint8_t buf [MAVLINK_MAX_PACKET_LEN];
    int len = comm_try_read (com, buf, MAVLINK_MAX_PACKET_LEN);
    if (len < 0)
        return -1;

    mavlink_message_t msg;
    mavlink_status_t stat;
    for (int i = 0; i < len; i++)
    {
        if (mavlink_parse_char (1, buf[i], &msg, &stat))
        {
            switch (msg.msgid)
            {
            case MAVLINK_MSG_ID_heartbeat:
                /* code */
                break;
            case MAVLINK_MSG_ID_query_result:
                ble_process_mavlink (ble, &msg);
                break;
            
            default:
                break;
            }
        }
    }
    
    return 0;     
}

int main()
{
    init_main ("203.255.57.123", "4869");

    while (1)
    {
        ble_process_hci_evt (ble, 10);//pos_scan_perimeter (pos, 100);
        exec_query ();
        
        comm_do_write (com, 100);
        comm_do_read (com, 100);

        receive_pkt ();

        ble_handle_conn (ble, 1000);
        ble_read_rssis (ble, 100);

        pos_estimate_position (pos, 100);
    }

    return 0;
}