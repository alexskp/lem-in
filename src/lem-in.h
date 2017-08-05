
#ifndef LEM_IN_H
#define LEM_IN_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct          adjacent
{
    struct room         *ptr_adj;
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


typedef struct          path_node
{
    char                *name;
    struct path_node    *next;
} path_node;

typedef struct          path
{
    int                 len;
    path_node           *path;
    struct path         *next;
} path;

typedef struct          elem
{
    room                *content;
    struct elem         *next;
} elem;

/*
*   parse.c
*/
void parse_ants(graph *);
void parse_rooms(graph *);
void parse_links(graph *);
void check_anthill(graph *);
graph *parse_map(void);

/*
*   room_list.c
*/
room *add_room(room **head, char *name, int x, int y, int dist);
room *get_nth_room(room *head, int n);
room *get_last_room(room *head);
room *get_room(room *head, char *name);

/*
*   adjacent_list.c
*/
adj *add_adj(adj **head, room *ptr_adj);
adj *get_nth_adj(adj *head, int n);
adj *get_last_adj(adj *head);
adj *get_adj(adj *head, char *name);

/*
*   queue.c
*/
void push(elem **head, room* content);
room *pop(elem **head);

/*
*   graph.c
*/
path *search_paths(graph *);
void print_graph(graph *);

/*
*   error.c
*/
void error(char *message);

#endif
