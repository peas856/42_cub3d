NAME = main

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLX = mlx

LXFLAGS = -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

SRC = main.c \
	parse.c \
	parse_map.c \
	parse_tools.c\
	util.c \
	gnl.c \
	key.c \
	screen.c \
	util_check.c \

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
