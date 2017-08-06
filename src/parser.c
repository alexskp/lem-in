
#include "lem-in.h"

#define BUFF_SIZE       100
#define REGULAR_ROOM    0
#define START_ROOM      1
#define END_ROOM        2

static int iscomment(char *str)
{
    if (str[0] == '#' && str[1]!= '#')
    {
        printf("%s", str);
        return 1;
    }
    else
        return 0;
}

void parse_ants(graph *anthill)
{
    int ants;
    char buff[BUFF_SIZE];
    while (fgets(buff, BUFF_SIZE, stdin) != NULL  && iscomment(buff));

    if ((ants = atoi(buff)) > 0)
        anthill->ants = ants;
    else
        error("Error! Incorrect number of ants...\n");
    printf("%d\n", ants);
}

static char *dup_str(char *str)
{
    char *new;
    if (new = (char *)my_malloc(sizeof(char) * strlen(str) + 1))
    {
        strcpy(new, str);
        return new;
    }
    else
        return NULL;
}

void parse_links(graph *anthill)
{
    char buff[BUFF_SIZE];
    char *token_1;
    char *token_2;
    char *sep = "-\n";
    room *room_1;
    room *room_2;
    room *ptr_adj;

    while (fgets(buff, BUFF_SIZE, stdin) != NULL)
    {
        if (iscomment(buff))
            continue;
        if ((token_1 = strtok(buff, sep)) != NULL
           && (token_2 = strtok(NULL, sep)) != NULL
           && (room_1 = get_room(anthill->rooms, token_1)) != NULL
           && (room_2 = get_room(anthill->rooms, token_2)) != NULL
           && strcmp(token_1, token_2))
        {
            ptr_adj = get_room(anthill->rooms, token_2);
            add_adj(&room_1->adjacent, ptr_adj);
            ptr_adj = get_room(anthill->rooms, token_1);
            add_adj(&room_2->adjacent, ptr_adj);

            printf("%s-%s\n", token_1, token_2);
        }
        else if (token_1)
            error("Error! Incorrect input...");
        else
            return;
    }
}

void parse_rooms(graph *anthill)
{
    char buff[BUFF_SIZE];

    room *new_room;
    room **rooms = &anthill->rooms;

    char start_room[]   = "##start";
    char end_room[]     = "##end";
    char sep[]          = " \t\n";
    char *token_name;
    char *token_x;
    char *token_y;
    char *room_name;
    int  room_type      = REGULAR_ROOM;

    while (fgets(buff, BUFF_SIZE, stdin) != NULL)
    {
        if (iscomment(buff))
            continue;
        if ((token_name = strtok(buff, sep)) != NULL
           && (token_x = strtok(NULL, sep)) != NULL
           && (token_y = strtok(NULL, sep)) != NULL)
        {
            if (!get_room(*rooms, token_name))
            {
                room_name = dup_str(token_name);
                new_room = add_room(rooms, room_name, atoi(token_x), atoi(token_y), INF);
            }
            else
                error("Error! Room already exist!");

            if (room_type == START_ROOM)
            {
                anthill->start_room = new_room;
                new_room->dist = 0;
                room_type = REGULAR_ROOM;
            }
            else if (room_type == END_ROOM)
            {
                anthill->end_room = new_room;
                room_type = REGULAR_ROOM;
            }
            printf("%s %s %s\n", room_name, token_x, token_y);
        }
        else if (token_name && strcmp(start_room, token_name) == 0)
        {
            printf("%s\n", start_room);
            if (!anthill->start_room)
                room_type = START_ROOM;
            else
                error("Error! Start room already exist...\n");
        }
        else if (token_name && strcmp(end_room, token_name) == 0)
        {
            printf("%s\n", end_room);
            if (!anthill->end_room)
                room_type = END_ROOM;
            else
                error("Error! End room already exist...\n");
        }
        else
        {
            ungetc('\n', stdin);
            for (int i = strlen(buff); i >= 0; i--)
                ungetc(buff[i], stdin);
            return;
        }
    }
    error("Error! There are no links...");
}

void check_anthill(graph *anthill)
{
    if (!anthill->start_room)
        error("Error! No start room!");
    if (!anthill->end_room)
        error("Error! No end room!");
}

graph *parse_map(void)
{
    graph *anthill = (graph *)my_malloc(sizeof(graph));

    parse_ants(anthill);
    parse_rooms(anthill);
    parse_links(anthill);

    check_anthill(anthill);

    return anthill;
}
