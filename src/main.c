
#include "lem-in.h"

void print_graph(graph *);

int main(void)
{
    graph *anthill = parse_map();
    path *paths = create_paths(anthill);


    
    print_paths(paths);

    free_graph(anthill);
    free_paths(&paths);

    printf("LEAKS: %d\n", malloc_counter);
    exit(EXIT_SUCCESS);
}
