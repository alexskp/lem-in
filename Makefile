
EXEC = lem-in

CC = gcc

CFLAGS = -g -c -Wall -Werror -Wextra

SRCDIR = src

SRC = main.c \
	   adjacent_list.c \
	   debug.c \
	   error.c \
	   free.c \
	   graph_tools.c \
	   parser.c \
	   path_group_searcher.c \
	   path_list.c \
	   queue.c \
	   room_list.c \
	   step_generator.c

OBJ = $(addprefix $(SRCDIR)/, $(SRC:.c=.o))

.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<


.PHONY: clean
clean:
	rm -f $(OBJ)

.PHONY: fclean
fclean:
	rm -f $(OBJ)
	rm -f $(EXEC)

.PHONY: re
re: fclean all
