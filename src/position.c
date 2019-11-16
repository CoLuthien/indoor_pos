#include "position.h"

#define MAX_PKT_LEN 8

struct parsed_query
{
    bdaddr_t addrs[MAX_PKT_LEN];
    uint8_t status[MAX_PKT_LEN];
    float x[MAX_PKT_LEN];
    float y[MAX_PKT_LEN];
};

static int pos_parse_query (struct position_t* self, struct parsed_query* res);

int pos_scan_perimeter (struct position_t* self)
{
    
    
}