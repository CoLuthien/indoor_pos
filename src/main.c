#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include "ble.h"
#include "position.h"
#include "comm.h"
#include "mavlink.h"


struct ble_t* ble = NULL;
struct comm_t* com = NULL;
struct position_t* pos = NULL;


void read_server_attr (char* addr, char* port)
{
    FILE* fp = fopen ("/etc/pos.addr.conf", "r");
    uint8_t buf[128];
    
    size_t len = fread (buf, sizeof(char), 128, fp);
    memcpy(addr, buf, len);
    fclose (fp);

    fp = fopen ("/etc/pos.port.conf", "r");
    len = fread (buf, sizeof(char), 128, fp);
    memcpy (port, buf, len);
    fclose (fp);
}

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
                len = mavlink_msg_heartbeat_pack(1, 1, &msg, &ble->my_addr, 1, 0);
                mavlink_msg_to_send_buffer (buf, &msg);
                comm_append_write (com, buf, len);
                break;
            case MAVLINK_MSG_ID_query_result:
                ble_process_mavlink (ble, &msg);
                break;
            case MAVLINK_MSG_ID_command:
                break;            
            case MAVLINK_MSG_ID_path_response:

                break;
            default:
                break;
            }

            break;
        }
    }
    
    return 0;     
}

int exec_report ()
{
    uint8_t buf[MAVLINK_MAX_PACKET_LEN];

    int len = pos_get_stat_report (pos, buf);
    comm_append_write (com, buf, len);
    
    len = ble_get_node_report (ble, buf);
    comm_append_write (com, buf, len);
    
    return 0;
}

int main()
{
    char addr[128], port[128];
    read_server_attr (addr, port);

    printf("read addr: %s\nread port: %s\n", addr, port);
    init_main (addr, port);

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

//        exec_report ();
    }

    return 0;
}