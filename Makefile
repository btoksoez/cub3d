NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I/opt/X11/include
LIBFT = includes/libft/libft.a
COMPRESS = ar rcs
RM = rm -rf

SRC_DIR = sources
SRC = $(wildcard $(SRC_DIR)/*.c)
SRC_BONUS_DIR = sources_bonus
SRC_BONUS = $(wildcard $(SRC_BONUS_DIR)/*.c)

OBJ_DIR = objects
OBJ = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))
OBJ_BONUS_DIR = bonus_objects
OBJ_BONUS = $(addprefix $(OBJ_BONUS_DIR)/,$(notdir $(SRC_BONUS:.c=.o)))

# # Linux
# MLX_DIR = includes/minilibx-linux
# MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
# MLX_INC = -I$(MLX_DIR) -I$(MLX_DIR)/linux
# MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

# Mac
MLX_DIR = includes/minilibx-mac
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INC = -I$(MLX_DIR)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

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

bonus: $(NAME)_bonus

$(NAME)_bonus: $(OBJ_BONUS_DIR) $(OBJ_BONUS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(MLX_FLAGS) $(LIBFT) -o $(NAME)_bonus
	@echo "$(CYAN)make$(RESET)   bonus   $(GREEN)[OK]$(RESET)"

$(LIBFT):
	@$(MAKE) -s -C ./includes/libft --no-print-directory

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_BONUS_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@$(MAKE) -C ./includes/libft clean --no-print-directory
	@echo "$(ORANGE)$@$(RESET)  $(NAME) $(GREEN)[OK]$(RESET)"
#	@echo "$(ORANGE)$@$(RESET)  bonus $(GREEN)[OK]$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME)_bonus
	@$(MAKE) -C ./includes/libft fclean --no-print-directory
	@echo "$(RED)$@$(RESET) $(NAME) $(GREEN)[OK]$(RESET)"
#	@echo "$(RED)$@$(RESET) bonus $(GREEN)[OK]$(RESET)"

re: fclean all

v: re
	@echo "\n"
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) maps/map2.ber

v_mac: re
	@echo "\n"
	leaks -atExit -- ./$(NAME) maps/map2.ber

.PHONY: all clean fclean re bonus
