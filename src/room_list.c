
#include "lem-in.h"


room *get_nth_room(room *head, int n)
{
    int counter = 0;
    while (counter < n && head)
    {
        head = head->next;
        counter++;
    }
    return head;
}

room *get_last_room(room *head)
{
    if (head == NULL)
        return head;
    while (head->next)
        head = head->next;
    return head;
}

room *get_room(room *head, char *name)
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
room *add_room(room **head, char *name, int x, int y, int dist)
{
    if (!get_room(*head, name))
    {
        room *last = get_last_room(*head);
        room *new = (room *)malloc(sizeof(room));
        new->name = name;
        new->x = x;
        new->y = y;
        new->dist = dist;
        new->adjacent = NULL;
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
