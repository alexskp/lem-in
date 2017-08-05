
#include "lem-in.h"

void print_graph(graph *);

int main(void)
{

    graph *anthill = parse_map();

    print_graph(anthill);

    search_paths(anthill);


    exit(EXIT_SUCCESS);
}
