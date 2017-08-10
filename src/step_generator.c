#include "lem-in.h"


static void move_on(adj *ant_pos[], int i)
{
    int k = 0;
    while (k < i)
    {
        if (ant_pos[k])
        {
            printf("L%d-%s ", k + 1, ant_pos[k]->adj_room->name);
            ant_pos[k] = ant_pos[k]->next;
        }
        k++;
    }
    printf("\n");
}

void print_steps(path *paths, int ants)
{
    path *nth_path;
    adj *ant_pos[ants];
    int i, j, k;

    printf("\n");
    i = 0;
    k = 0;
    while (k < max_steps(paths))
    {
        j = 0;
        while ((nth_path = get_nth_path(paths, j++)))
        {
            if (nth_path->ants > 0)
            {
                ant_pos[i++] = nth_path->path_node->next;
                nth_path->ants--;
            }
        }
        move_on(ant_pos, i);
        k++;
    }
}
