
#ifndef LEM_IN_H
#define LEM_IN_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


typedef struct adj
{
    char *name;
    struct adj *next;
} adj;

typedef struct room
{
    char *name;
    int x;
    int y;
    struct adj *adjacent;
    struct room *next;
} room;

typedef struct graph
{
    int ants;
    room *start_room;
    room *end_room;
    room *rooms;
} graph;

/*
*   parse.c
*/
void parse_ants(graph *anthill);
void parse_rooms(graph *anthill);
void parse_links(graph *anthill);
void check_anthill(graph *anthill);
graph *parse();

/*
*   room_list.c
*/
room *add_room(room **head, char *name, int x, int y, adj *adjacent);
room *get_nth_room(room *head, int n);
room *get_last_room(room *head);
room *get_room(room *head, char *name);
/*
*   adjacent_list.c
*/
adj *add_adj(adj **head, char *name);
adj *get_nth_adj(adj *head, int n);
adj *get_last_adj(adj *head);
adj *get_adj(adj *head, char *name);

/*
*   error.c
*/
void error(char *message);

#endif
