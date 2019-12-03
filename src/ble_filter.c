#include "ble_filter.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>



struct dup_elem* find_dup_entry (struct list* check_list, bdaddr_t addr)
{
    if (list_empty (check_list))
        return NULL;
    
    struct list_elem* end = list_end (check_list);
    struct list_elem* e = NULL;
    struct dup_elem* cur;

    for (e = list_front (check_list);
         e != end;
         e = list_next (e))
    {
        cur = list_entry (e, struct dup_elem, elem);

        if (bacmp (&cur->addr, &addr) == 0)
        {
            return cur;
        }
    }

    return NULL;
}

struct dup_elem* create_dup_entry (bdaddr_t addr)
{
    struct dup_elem* elem = malloc (sizeof(struct dup_elem));
    if (NULL == elem)
        return NULL;

    bacpy (&elem->addr, &addr);

    return elem;    
}

void rm_dup_entry_byaddr (struct list* check_list, bdaddr_t addr)
{
    struct dup_elem* dup = find_dup_entry (check_list, addr);
    ASSERT (dup != NULL);

    list_remove (&dup->elem);

    free (dup);
    dup = NULL;
}

void rm_dup_entry (struct list* check_list, struct dup_elem* dup)
{
    ASSERT (dup != NULL);

    list_remove (&dup->elem);
    free (dup);
    dup = NULL;
}

void insert_dup_entry (struct list* check_list, struct dup_elem* dup)
{
    list_push_front (check_list, &dup->elem);
}

void reset_dup_entry (struct list* check_list)
{
    if (list_empty (check_list))
    {
        return;
    }
    struct list_elem* end = list_end (check_list);
    struct list_elem* e = NULL;
    struct dup_elem* cur = NULL;
    for (e = list_front (check_list);
         e != end;
        )
    {
        cur = list_entry (e, struct dup_elem, elem);
        e = list_next (e);

        printf("%s\n", batostr(&cur->addr));
        rm_dup_entry (check_list, cur);
    }
}
