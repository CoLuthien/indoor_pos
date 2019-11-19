#ifndef _NODE_CTL_H
#define _NODE_CTL_H


#include "node.h"
#include "list.h"
#include "debug.h"

#include <stdint.h>

struct node_list
{
    struct list head;
    int len;
};

void node_list_init (struct node_list* target);
struct node_basic* node_get_elem (struct list_elem* e);

struct node_basic* node_create (bdaddr_t addr, uint8_t status);

void node_promote (struct node_basic* target);
void node_demote (struct node_basic* target);
void node_insert (struct node_list* target_list, struct node_basic* target);
void node_remove_frm_list (struct node_list* target_list, struct node_basic* target);// remove from list, don't care what list.
void node_destroy (struct node_basic* target); // will not handle list operation. before use, target must not in list.

struct node_basic* node_find (bdaddr_t addr, struct node_list* target_list);



#endif