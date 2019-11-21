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
    init_main ("203.255.59.254", "7777");
    prepare_flight ();

    while (1)
    {

    }

    return 0;
}