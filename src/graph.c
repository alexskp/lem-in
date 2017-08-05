
#include "lem-in.h"



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
            printf("_________________: %s\n", adjacent->name);
        }
        j = 0;
    }
}
