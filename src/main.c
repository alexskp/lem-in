
#include "lem-in.h"

void print_graph(graph *);

int main(void)
{
    graph *anthill = parse_map();
    path *paths = get_path_group(anthill);

    // print_path_group(paths);

    print_steps(paths, anthill->ants);

    free_graph(anthill);
    free_paths(&paths);

    exit(EXIT_SUCCESS);
}
