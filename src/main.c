
#include "lem-in.h"

void print_graph(graph *);

int main(void)
{
    graph *anthill = parse_map();

    search_paths(anthill);
    
    print_graph(anthill);

    free_graph(anthill);
    exit(EXIT_SUCCESS);
}
