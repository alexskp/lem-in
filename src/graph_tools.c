
#include "lem-in.h"


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
