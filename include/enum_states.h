#ifndef _ENUM_STATES_H
#define _ENUM_STATES_H

enum positioning_method
{
    INIT = 0,
    ONLY_BLE,
    ONLY_GPS,
    BOTH
};

enum system_status 
{
    SYS_INIT = 0,
    FORWARD_STEP,
    BACKSTEP
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