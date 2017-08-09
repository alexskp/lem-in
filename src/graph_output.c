
#include "lem-in.h"


void print_steps()
{
    // TODO
}

void print_paths(path *paths)
{
    path *nth_path;
    adj *nth_node;

    int i = 0;
    int j = 0;

    while ((nth_path = get_nth_path(paths, i++)))
    {
        j = nth_path->len;
        printf("LENGTH: %d ANTS: %d\t", nth_path->len, nth_path->ants);
        while ((nth_node = get_nth_adj(nth_path->path_node, j--)))
        {
            printf("%s%s", nth_node->adj_room->name, (j >= 0) ? " - " : "\n");
        }
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
