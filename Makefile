
EXEC = lem-in

CC = gcc

CFLAGS = -g -c -Wall -Werror -Wextra

SRCDIR = src

BUILDDIR = obj

SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(patsubst $(SRCDIR)/%, %, $(SRC))
OBJ := $(patsubst %.c, %.o, $(OBJ))
OBJ := $(addprefix $(BUILDDIR)/,$(OBJ))

.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
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
