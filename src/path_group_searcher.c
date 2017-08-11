
#include "lem-in.h"


adj *get_path(graph *anthill)
{
    int j;
    room *nth_room = anthill->end_room;
    adj *path_node = NULL;
    adj *adjacent;

    scan_shortest_path(anthill);
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

path *create_path_group(graph *anthill)
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
    hard_reset_dists(anthill);
    return paths;
}

path *get_path_group(graph *anthill)
{
    path *paths = NULL;
    int i = 0;
    while (get_nth_adj(anthill->start_room->adjacent, i++))
    {
        free_paths(&paths);
        paths = search_optimal_path_group(anthill);
    }
    return paths;
}

path *search_optimal_path_group(graph *anthill)
{
    path *paths = create_path_group(anthill);
    int original;
    if (paths)
    {
        apportion_ants(paths, anthill->ants);
        original = max_steps(paths);
    }
    else
    {
        free_graph(anthill);
        error("Error! There are no paths.");
    }
    path *nth_path;
    adj *nth_node;
    path *alt_paths = NULL;

    int spec_case = 0;
    adj *spec_path = NULL;
    room *room_1 = NULL;
    room *room_2 = NULL;

    room *tmp1 = NULL;
    room *tmp2 = NULL;

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
                    alt_paths = create_path_group(anthill);
                    if (spec_case)
                    {
                        spec_path = NULL;
                        add_adj(&spec_path, room_1);
                        add_adj(&spec_path, room_2);
                        add_path(&alt_paths, spec_path, 1);
                    }
                    if (!alt_paths)
                    {
                        link(nth_node->adj_room, nth_node->next->adj_room);
                        continue;
                    }

                    apportion_ants(alt_paths, anthill->ants);
                    if (max_steps(alt_paths) < original)
                    {
                        tmp1 = nth_node->adj_room;
                        tmp2 = nth_node->next->adj_room;
                    }
                    free_paths(&alt_paths);
                    link(nth_node->adj_room, nth_node->next->adj_room);
                }
            }
        }
    }
    if (tmp1)
    {
        free_paths(&paths);
        unlink(tmp1, tmp2);
        alt_paths = create_path_group(anthill);
        apportion_ants(alt_paths, anthill->ants);
        return alt_paths;
    }
    else
        return paths;
}

void apportion_ants(path *paths, int ants)
{
    int i = 0;
    int num_of_paths = 0;
    int min_steps = INF;
    int min_steps_path;
    path *nth_path;

    while ((nth_path = get_nth_path(paths, i++)))
        num_of_paths++;

    if (num_of_paths == 1)
    {
        paths->ants = ants;
        paths->steps = ants + paths->len - 1;
        return;
    }

    while (ants)
    {
        i = 0;
        while ((nth_path = get_nth_path(paths, i++)))
        {
            nth_path->steps = nth_path->len + nth_path->ants - 1;
            if (nth_path->steps < min_steps)
            {
                min_steps_path = i - 1;
                min_steps = nth_path->steps;
            }
        }
        min_steps = INF;
        nth_path = get_nth_path(paths, min_steps_path);
        nth_path->ants++;
        nth_path->steps++;
        ants--;
    }
}
