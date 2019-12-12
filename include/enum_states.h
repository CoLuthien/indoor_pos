#ifndef _ENUM_STATES_H
#define _ENUM_STATES_H

enum sys_stat
{
    INIT = 0,
    ONLY_BLE,
    ONLY_GPS,
    BOTH_BG,
    FAIL_SAFE
};

enum component
{
    bluetooth = 1,
    position
};

enum command
{
    STAT_REPORT = 0
};

#endif