TARGET		= push_swap

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC_S = push_swap.c \
		includes/a_operations.c \
		includes/above_algorithm.c \
		includes/additions.c \
		includes/b_operations.c \
		includes/check.c \
		includes/find_sort.c \
		includes/free.c \
		includes/init.c \
		includes/main_algo.c \
		includes/mediumalgorithm.c \
		includes/microalgorithm.c \
		includes/minialgorithm.c \
		includes/preparations.c \
		includes/pushes.c

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