
#include "lem-in.h"


int malloc_counter = 0;

void *my_malloc(size_t size)
{
    malloc_counter++;
    return malloc(size);
}

void my_free(void *ptr)
{
    free(ptr);
    malloc_counter--;
}

void print_path_group(path *paths)
{
    path *nth_path;
    adj *nth_node;

    int i, j;

    i = 0;
    while ((nth_path = get_nth_path(paths, i++)))
    {
        j = 0;
        printf("LENGTH: %d ANTS: %d\t", nth_path->len, nth_path->ants);
        while ((nth_node = get_nth_adj(nth_path->path_node, j++)))
        {
            printf("%s%s", nth_node->adj_room->name, (j <= nth_path->len) ? " - " : "\n");
        }
    }
    printf("Steps: %d\n", max_steps(paths));
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
