
#include "lem-in.h"

path *get_nth_path(path *head, int n)
{
    int counter = 0;
    while (counter < n && head)
    {
        head = head->next;
        counter++;
    }
    return head;
}

path *get_last_path(path *head)
{
    if (head == NULL)
        return head;
    while (head->next)
        head = head->next;
    return head;
}

path *add_path(path **head, adj *path_node, int len)
{
    path *last = get_last_path(*head);
    path *new = (path *)malloc(sizeof(path));
    new->path_node = path_node;
    new->len = len;
    new->ants = 0;
    new->steps = 0;
    new->next = NULL;
    if (last)
        last->next = new;
    else
        (*head) = new;
    return new;
}
