NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a
COMPRESS = ar rcs
RM = rm -rf

OBJ_DIR = objects
SRC_DIR = sources
SRC_DIRS = $(wildcard $(SRC_DIR)/*)
SRC = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# Mlx Library
MLX_DIR = includes/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_INC = -I$(MLX_DIR) -I$(MLX_DIR)/linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

# Colours
GREEN = \033[1;32m
ORANGE = \033[1;33m
RED = \033[1;31m
CYAN = \033[1;36m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT) -o $(NAME)
	@echo "$(CYAN)make$(RESET)   $@ $(GREEN)[OK]$(RESET)"

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR) --no-print-directory

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(foreach dir, $(SRC_DIRS), $(OBJ_DIR)/$(notdir $(dir)))

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(ORANGE)$@$(RESET)  $(NAME) $(GREEN)[OK]$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(RED)$@$(RESET) $(NAME) $(GREEN)[OK]$(RESET)"

re: fclean all

v: re
	@echo "\n"
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) maps/map2.ber

.PHONY: all clean fclean re v
