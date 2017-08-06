
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
        if (!strcmp(name, head->adj_room->name))
            return head;
        else
            head = head->next;
    }
    return NULL;
}

/* return NULL if already exist */
adj *add_adj(adj **head, room *adj_room)
{
    if (!get_adj(*head, adj_room->name))
    {
        adj *last = get_last_adj(*head);
        adj *new = (adj *)my_malloc(sizeof(adj));
        new->adj_room = adj_room;
        new->next = NULL;
        if (last)
            last->next = new;
        else
            (*head) = new;
        return new;
    }
    else
        return NULL;
}

void free_adjacent(adj **head)
{
    adj *del;
    if (*head == NULL)
        return;
    while (*head)
    {
        del = (*head);
        (*head) = del->next;
        my_free(del);
    }
}
