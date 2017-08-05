
#include "lem-in.h"


adj *get_nth_adj(adj *head, int n)
{
    int counter = 0;
    while (counter < n && head)
    {
        head = head->next;
        counter++;
    }
    return head;
}

adj *get_last_adj(adj *head)
{
    if (head == NULL)
        return head;
    while (head->next)
        head = head->next;
    return head;
}

adj *get_adj(adj *head, char *name)
{
    while (head)
    {
        if (!strcmp(name, head->ptr_adj->name))
            return head;
        else
            head = head->next;
    }
    return NULL;
}

/* return NULL if already exist */
adj *add_adj(adj **head, room *ptr_adj)
{
    if (!get_adj(*head, ptr_adj->name))
    {
        adj *last = get_last_adj(*head);
        adj *new = (adj *)malloc(sizeof(adj));
        new->ptr_adj = ptr_adj;
        new->next = NULL;
        if (last)
            last->next = new;
        else
            *head = new;
        return new;
    }
    else
        return NULL;
}
