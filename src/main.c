
#include "lem-in.h"

void print_graph(graph *);

int main(void)
{
    graph *anthill = parse_map();
    path *paths = create_paths(anthill);

    search_alternative(anthill, paths);

    //print_paths(paths);

    free_graph(anthill);
    free_paths(&paths);

    exit(EXIT_SUCCESS);
}
