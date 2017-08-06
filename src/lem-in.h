
#ifndef LEM_IN_H
#define LEM_IN_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define INF             2147483647      /* max_int */

typedef struct          adjacent
{
    struct room         *adj_room;
    struct adjacent     *next;
} adj;

typedef struct          room
{
    char                *name;
    int                 x;
    int                 y;
    int                 dist;
    adj                 *adjacent;
    struct room         *next;
} room;

typedef struct          graph
{
    int                 ants;
    room                *start_room;
    room                *end_room;
    room                *rooms;
} graph;

typedef struct          elem
{
    room                *content;
    struct elem         *next;
} elem;

typedef struct          path
{
    int                 len;
    adj                 *path_node;
    struct path         *next;
} path;

/*
*   parse.c
*/
void parse_ants(graph *);
void parse_rooms(graph *);
void parse_links(graph *);
void check_anthill(graph *);
graph *parse_map(void);

/*
*   adjacent_list.c
*/
adj *add_adj(adj **head, room *ptr_adj);
adj *get_nth_adj(adj *head, int n);
adj *get_last_adj(adj *head);
adj *get_adj(adj *head, char *name);
void free_adjacent(adj **head);
/*
*   room_list.c
*/
room *add_room(room **head, char *name, int x, int y, int dist);
room *get_nth_room(room *head, int n);
room *get_last_room(room *head);
room *get_room(room *head, char *name);
void free_rooms(room **head);

/*
*   path_list.c
*/
path *add_path(path **head, adj *path_node);
path *get_nth_path(path *head, int n);
path *get_shortest_path(path *head);
path *get_last_path(path *head);
void free_paths(path **head);

/*
*   queue.c
*/
void push(elem **head, room* content);
room *pop(elem **head);

/*
*   graph.c
*/
void search_path(graph *);
adj *get_path(graph *);
path *create_paths(graph *);
void reset_dists(graph *);
void print_graph(graph *);
void print_paths(path *);
void free_graph(graph *);

/*
*   leak_control.c
*/
extern int malloc_counter;
void *my_maloc(size_t size);
void my_free(void *ptr);

/*
*   error.c
*/
void error(char *message);

#endif
