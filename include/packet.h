#ifndef _PACKET_H
#define _PACKET_H

enum sys_stat
{
    INIT = 0,
    ONLY_BLE,
    ONLY_GPS,
    BOTH_BG,
    FAIL_SAFE
};

enum command
{
    STAT_REPORT = 0
};

#endif