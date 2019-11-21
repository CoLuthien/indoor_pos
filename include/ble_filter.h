#ifndef _BLE_FILTER_H
#define _BLE_FILTER_H

#include "list.h"
#include <bluetooth/bluetooth.h>

struct dup_elem
{
    struct list_elem elem;
    bdaddr_t addr;
};

struct dup_elem* find_dup_entry (struct list* check_list, bdaddr_t addr);
struct dup_elem* create_dup_entry (bdaddr_t addr);
void rm_dup_entry_byaddr (struct list* check_list, bdaddr_t addr);
void rm_dup_entry (struct list* check_list, struct dup_elem* dup);
void insert_dup_entry (struct list* check_list, struct dup_elem* dup);

void reset_dup_entry (struct list* check_list);

#endif