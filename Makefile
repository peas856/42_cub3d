NAME = cub3D

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLX = mlx

LXFLAGS = -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

SRC = main \
	parse \
	parse_map \
	parse_tools \
	util_check \
	gnl \
	key \
	screen \
	util \
	draw \

FIL = $(addsuffix .c, $(addprefix src/, $(SRC)))

OBJ = $(FIL:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(OBJ)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
	