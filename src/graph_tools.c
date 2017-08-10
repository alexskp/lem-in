
#include "lem-in.h"

void scan_shortest_path(graph *anthill)
{
    elem *queue = NULL;
    room *current;
    adj  *adj_room;
    int i = 0;

    reset_dists(anthill);
    push(&queue, anthill->start_room);

    while (queue)
    {
        current = pop(&queue);
        i = 0;
        while ((adj_room = get_nth_adj(current->adjacent, i)))
          {
            if (adj_room->adj_room->dist != -1 &&
                adj_room->adj_room->dist > current->dist + 1)
            {
                adj_room->adj_room->dist = current->dist + 1;
                push(&queue, adj_room->adj_room);
            }
            i++;
        }
    }
}

void link(room *room_1, room *room_2)
{
    add_adj(&room_1->adjacent, room_2);
    add_adj(&room_2->adjacent, room_1);
}

void unlink(room *room_1, room *room_2)
{
    adj *adj_room_1 = get_adj(room_2->adjacent, room_1);
    adj *adj_room_2 = get_adj(room_1->adjacent, room_2);

    del_adj(&room_1->adjacent, adj_room_2);
    del_adj(&room_2->adjacent, adj_room_1);
}

void reset_dists(graph *anthill)
{
    room *nth_room;
    int i = 0;

    while ((nth_room = get_nth_room(anthill->rooms, i++)))
        if (nth_room->dist != -1)
            nth_room->dist = INF;
    anthill->start_room->dist = 0;
}

void hard_reset_dists(graph *anthill)
{
    room *nth_room;
    int i = 0;

    while ((nth_room = get_nth_room(anthill->rooms, i++)))
        nth_room->dist = INF;
    anthill->start_room->dist = 0;
}

int max_steps(path *paths)
{
    path *nth_path;
    int i = 0;
    int max_steps = 0;

    while ((nth_path = get_nth_path(paths, i++)))
    {
        if (nth_path->steps > max_steps)
            max_steps = nth_path->steps;
    }
    return max_steps;
}
