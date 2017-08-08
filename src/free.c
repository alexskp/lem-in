
#include "lem-in.h"

void free_adjacent(adj **head)
{
    adj *del;
    if (*head == NULL)
        return;
    while (*head)
    {
        del = (*head);
        (*head) = del->next;
        free(del);
    }
}

void free_rooms(room **head)
{
    room *del;
    if (*head == NULL)
        return;
    while (*head)
    {
        free_adjacent(&(*head)->adjacent);
        free((*head)->name);
        del = (*head);
        (*head) = (*head)->next;
        free(del);
    }
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
        free(del);
    }
}

void free_graph(graph *anthill)
{
    free_rooms(&anthill->rooms);
    free(anthill);
}
