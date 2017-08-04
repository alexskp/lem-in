
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
        if (!strcmp(name, head->name))
            return head;
        else
            head = head->next;
    }
    return NULL;
}

/* return NULL if already exist */
adj *add_adj(adj **head, char *name)
{
    if (!get_adj(*head, name))
    {
        adj *last = get_last_adj(*head);
        adj *new = (adj *)malloc(sizeof(adj));
        new->name = name;
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
