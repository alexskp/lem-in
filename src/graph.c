
#include "lem-in.h"



path *search_paths(graph *anthill)
{
    elem *queue = NULL;
    room *current;
    adj  *adj_room;
    int i = 0;

    push(&queue, anthill->start_room);

    while (queue)
    {
        current = pop(&queue);
        i = 0;
        while (adj_room = get_nth_adj(current->adjacent, i))
        {
            if (adj_room->ptr_adj->dist != -1 &&
                adj_room->ptr_adj->dist > current->dist + 1)
            {
                adj_room->ptr_adj->dist = current->dist + 1;
                push(&queue, adj_room->ptr_adj);
            }
            i++;
        }
    }

    printf("LENGTH OF THE SHORTEST WAY: %d\n", anthill->end_room->dist);

    //create_path()

    return NULL;
}

void print_graph(graph *anthill)
{
    int i = 0;
    int j = 0;
    room *nth_room;
    adj *adjacent;

    printf("\n::::::START_ROOM::::::: %s\n", anthill->start_room->name);
    printf(":::::::END_ROOM:::::::: %s\n\n", anthill->end_room->name);
    while (nth_room = get_nth_room(anthill->rooms, i))
    {
        i++;
        printf("ROOM: %s(%d, %d), adjacent:\t distance: %d\n", nth_room->name,
               nth_room->x, nth_room->y, nth_room->dist);
        while (adjacent = get_nth_adj(nth_room->adjacent, j))
        {
            j++;
            printf("_________________: %s\n", adjacent->ptr_adj->name);
        }
        j = 0;
    }
}

void free_graph(graph *anthill)
{
    free_rooms(&anthill->rooms);
    my_free(anthill);
}
