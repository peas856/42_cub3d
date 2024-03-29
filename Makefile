NAME = cub3D

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLX_NAME = mlx
MLX_DIR = ./minilibx
MLX = $(addprefix $(MLX_DIR)/, libmlx.a)

LXFLAGS = -framework OpenGL -framework AppKit

HEADER = cub3d.h

SRCS_DIR = ./src

SRCS_NAME = main.c \
			parse.c \
			parse_map.c \
			parse_tools.c\
			util.c \
			gnl.c \
			key.c \
			screen.c \
			util_check.c \
			draw.c\

SRC = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR) all
	$(CC) $(CFLAGS) -L$(MLX_DIR) -l$(MLX_NAME) $(LXFLAGS) $^ -o $@

$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -I$(MLX_DIR) -I$(SRCS_DIR) -c $< -o $@

clean:
	$(MAKE) -C $(MLX_DIR) clean
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
