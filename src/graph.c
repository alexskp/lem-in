
#include "lem-in.h"


void search_path(graph *anthill)
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

adj *get_path(graph *anthill)
{
    int j;
    room *nth_room = anthill->end_room;
    adj *path_node = NULL;
    adj *adjacent;

    search_path(anthill);
    if (nth_room->dist == INF)
        return NULL;

    if (get_adj(anthill->start_room->adjacent, anthill->end_room))
    {
        unlink(anthill->start_room, anthill->end_room);
        add_adj(&path_node, anthill->start_room);
        add_adj(&path_node, anthill->end_room);
        search_path(anthill);
        return path_node;
    }

    while (nth_room->dist != 0)
    {
        j = 0;
        while ((adjacent = get_nth_adj(nth_room->adjacent, j++)))
        {
            if ((nth_room->dist - 1) == adjacent->adj_room->dist)
            {
                add_adj(&path_node, nth_room);
                if (nth_room != anthill->start_room && nth_room != anthill->end_room)
                {
                    nth_room->dist = -1;
                }
                nth_room = adjacent->adj_room;
                break;
            }
        }
    }
    add_adj(&path_node, anthill->start_room);
    return path_node;
}

path *create_paths(graph *anthill)
{
    path *paths = NULL;
    adj *path_node;
    adj *checker;
    int len;

    while ((path_node = get_path(anthill)))
    {
        len = 0;
        checker = path_node;
        while (checker->next)
        {
            checker = checker->next;
            len++;
        }
        add_path(&paths, path_node, len);
        reset_dists(anthill);
    }
    return paths;
}

void unlink(room *room_1, room *room_2)
{
    adj *adj_room_1 = get_adj(room_2->adjacent, room_1);;
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

void print_paths(path *paths)
{
    path *nth_path;
    adj *nth_node;

    int i = 0;
    int j = 0;

    while ((nth_path = get_nth_path(paths, i++)))
    {
        printf("LENGTH: %d\t", nth_path->len);
        while ((nth_node = get_nth_adj(nth_path->path_node, j++)))
        {
            printf("%s - ", nth_node->adj_room->name);
        }
        printf("\n");
        j = 0;
    }
}

void print_graph(graph *anthill)
{
    room *nth_room;
    adj *adjacent;

    int i = 0;
    int j = 0;

    printf("\n::::::START_ROOM::::::: %s\n", anthill->start_room->name);
    printf(":::::::END_ROOM:::::::: %s\n\n", anthill->end_room->name);
    while ((nth_room = get_nth_room(anthill->rooms, i++)))
    {
        j = 0;
        printf("ROOM: %s(%d, %d)\t min distance from start room: %d\n",
               nth_room->name, nth_room->x, nth_room->y, nth_room->dist);
        while ((adjacent = get_nth_adj(nth_room->adjacent, j++)))
            printf("_____: %s\n", adjacent->adj_room->name);
    }
}

void free_graph(graph *anthill)
{
    free_rooms(&anthill->rooms);
    free(anthill);
}
