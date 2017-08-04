
EXECUTABLE = lem-in

CC = gcc

CFLAGS = -g -c -Wall -Wextra

SRCDIR = src

SRC = main.c \
		parse.c \
		adjacent_list.c \
		room_list.c \
		error.c

OBJ = $(addprefix $(SRCDIR)/, $(SRC:.c=.o))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) -o $(EXECUTABLE) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<


.PHONY: clean fclean re
clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ)
	rm -f $(EXECUTABLE)

re: fclean all clean
