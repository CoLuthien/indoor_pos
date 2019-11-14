#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#include "node_ctl.h"


inline void node_list_init (struct node_list* target)
{
    list_init(&target->head);
    target->len = 0;
}

struct node_basic* node_create (bdaddr_t addr, uint8_t status)
{
    struct node_basic* node = malloc(sizeof(struct node_basic));

    if (NULL == node) 
        return NULL;

    bacpy(&node->addr, &addr);
    node->status = FOUND;
    
    return node;
}
void node_destroy (struct node_basic* target)
{
    ASSERT(target->status == REMOVE);
    free(target);
}

void node_promote (struct node_basic* target)
{
    target = 
        realloc(target, sizeof(struct node_basic) +
                        sizeof(struct node_info));
}

void node_demote (struct node_basic* target)
{
    target = realloc(target, sizeof(struct node_basic));
}

void node_insert (struct node_list* target_list, struct node_basic* target)
{
    target_list->len += 1;
    list_push_back (&target_list->head, &target->elem);
}

void node_remove_frm_list (struct node_list* target_list, struct node_basic* target)
{
    target_list->len -= 1;
    list_remove (&target->elem);
}

struct node_basic* node_find (bdaddr_t addr, struct node_list* target_list)
{
    if (target_list->len == 0)
    {
        return NULL;
    }
    struct node_basic* cur = NULL;
    struct list* list = &target_list->head;
    struct list_elem* end = list_end (list);
    for (struct list_elem* e = list_front (list);
         e != end;
         e = list_next(e))
    {
        cur = list_entry (e, struct node_basic, elem);
        if (bacmp(&addr, &cur->addr) == 0)
        {
            break;
        }

    }
    return cur;
}



