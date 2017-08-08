
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
        add_adj(&path_node, anthill->end_room);
        add_adj(&path_node, anthill->start_room);
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

// path *get_paths(graph *anthill)
// {
//     path *paths = create_paths(anthill);
//     paths = check_alternative(anthill, paths);
//     return paths;
// }

void search_alternative(graph *anthill, path *paths)
{
    print_paths(paths);
    printf("\nAlternative cases: \n");

    path *nth_path;
    adj *nth_node;
    path *alt_paths = NULL;

    int spec_case = 0;
    adj *spec_path = NULL;
    room *room_1 = NULL;
    room *room_2 = NULL;

    int i = 0;
    int j = 0;

    while ((nth_path = get_nth_path(paths, i++)))
    {
        if (nth_path->len == 1)
        {
            spec_case = 1;
            room_1 = nth_path->path_node->adj_room;
            room_2 = nth_path->path_node->next->adj_room;
            break;
        }
    }

    i = 0;

    while ((nth_path = get_nth_path(paths, i++)))
    {
        j = 0;
        if (nth_path->len > 1)
        {
            while ((nth_node = get_nth_adj(nth_path->path_node, j++)))
            {
                if (nth_node->next)
                {
                    unlink(nth_node->adj_room, nth_node->next->adj_room);
                    hard_reset_dists(anthill);
                    alt_paths = create_paths(anthill);
                    if (spec_case)
                    {
                        spec_path = NULL;
                        add_adj(&spec_path, room_1);
                        add_adj(&spec_path, room_2);
                        add_path(&alt_paths, spec_path, 1);
                    }
                    print_paths(alt_paths);
                    printf("\n");
                    free_paths(&alt_paths);
                    link(nth_node->adj_room, nth_node->next->adj_room);
                }
            }
        }
    }
}
