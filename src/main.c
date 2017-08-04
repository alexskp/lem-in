
#include "lem-in.h"


int main(void)
{

    graph *anthill = parse();

    int i = 0;
    int j = 0;
    room *nth_room;
    adj *adjacent;

    printf("::::::START_ROOM::::::: %s\n", anthill->start_room->name);
    printf(":::::::END_ROOM:::::::: %s\n", anthill->end_room->name);
    while (nth_room = get_nth_room(anthill->rooms, i))
    {
        i++;
        printf("ROOM: %s\n", nth_room->name);
        while (adjacent = get_nth_adj(nth_room->adjacent, j))
        {
            j++;
            printf("___________%s_\n", adjacent->name);
        }
        j = 0;
    }

    // room *sup = get_room(anthill->rooms, "r3");
    //
    // //printf("FOUNDED! %s", sup->name);

    exit(EXIT_SUCCESS);
}
