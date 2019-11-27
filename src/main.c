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
    com = comm_init (serv_addr, serv_port);
    ASSERT (com != NULL);

    ble = ble_init ();
    pos = pos_init (ble, com);

    return 0;
}

int prepare_flight ()
{
    if (ble_enable_scan (ble) < 0)
        return -1;

    return 0;
}

int main()
{
    init_main ("203.255.57.123", "4869");
    prepare_flight ();

    while (1)
    {
        pos_scan_perimeter (pos, 10);
        pos_query_nodes (pos, 10);
        comm_do_write (com, 100);
        comm_do_read(com, 100);
        pos_process_queries(pos, 100);
        pos_prepare_estimation (pos, 100);
        pos_estimate_position (pos, 100);
    }

    return 0;
}