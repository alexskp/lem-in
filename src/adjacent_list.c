
#include "lem-in.h"


adj *get_nth_adj(adj *head, int n)
{
    if (n < 0)
        return NULL;
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

adj *get_adj(adj *head, room *adj_room)
{
    while (head)
    {
        if (adj_room == head->adj_room)
            return head;
        else
            head = head->next;
    }
    return NULL;
}

void del_adj(adj **head, adj *del)
{
    adj *tmp;
    int i = 0;
    if ((*head) == del)
    {
        tmp = (*head)->next;
        free(del);
        (*head) = tmp;
    }
    else
    {
        while ((tmp = get_nth_adj((*head), i++)))
        {
            if (tmp->next == del)
            {
                tmp->next = del->next;
                free(del);
            }
        }
    }
}

/* return NULL if already exist */
adj *add_adj(adj **head, room *adj_room)
{
    if (!get_adj(*head, adj_room))
    {
        adj *last = get_last_adj(*head);
        adj *new = (adj *)malloc(sizeof(adj));
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
