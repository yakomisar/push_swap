TARGET		= push_swap

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC_S = push_swap.c

OBJ_S = $(SRC_S:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) -I . -c $< -o $@

all:	$(TARGET)

$(TARGET): $(OBJ_S)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(OBJ_S)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

.PHONY: all clean fclean re