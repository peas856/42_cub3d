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

FIL = $(addsuffix .c, $(addprefix src/, $(SRC)))

OBJ = $(FIL:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[0;33mCompiling..."
	$(CC) -o $(NAME) -L $(MLX) $(LXFLAGS) $(OBJ)
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning..."
	rm -rf $(OBJ)
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all
	