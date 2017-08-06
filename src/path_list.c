
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

path *get_shortest_path(path *head)
{
    path *min;
    int len = INF;
    while (head->next)
    {
        if (head->len < len)
            min = head;
    }
    return  min;
}

path *add_path(path **head, adj *path_node, int len)
{
    path *last = get_last_path(*head);
    path *new = (path *)my_malloc(sizeof(path));
    new->path_node = path_node;
    new->len = len;
    new->next = NULL;
    if (last)
        last->next = new;
    else
        (*head) = new;
    return new;
}

void free_paths(path **head)
{
    path *del;
    if (*head == NULL)
        return;
    while (*head)
    {
        free_adjacent(&(*head)->path_node);
        del = (*head);
        (*head) = (*head)->next;
        my_free(del);
    }
}
