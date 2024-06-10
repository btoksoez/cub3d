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

BONUS_SRC_DIR = sources_bonus
BONUS_SRC_DIRS = $(wildcard $(BONUS_SRC_DIR)/*)
BONUS_SRC = $(wildcard $(BONUS_SRC_DIR)/*.c $(BONUS_SRC_DIR)/*/*.c)
BONUS_OBJ = $(BONUS_SRC:%.c=$(OBJ_DIR)/%.o)

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	MLX_DIR = includes/minilibx-linux
	MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
	MLX_INC = -I$(MLX_DIR) -I$(MLX_DIR)/linux
	MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
	CFLAGS += -DLINUX
else
	MLX_DIR = includes/minilibx-mac
	MLX_LIB = $(MLX_DIR)/libmlx.a
	MLX_INC = -I$(MLX_DIR) -I$(MLX_DIR)/libmlx
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

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

bonus: $(OBJ_DIR) $(BONUS_OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(BONUS_OBJ) $(MLX_FLAGS) $(LIBFT) -o $(NAME)
	@echo "$(CYAN)make bonus$(RESET)   $@ $(GREEN)[OK]$(RESET)"

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR) --no-print-directory

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(foreach dir, $(SRC_DIRS), $(OBJ_DIR)/$(notdir $(dir))) $(foreach dir, $(BONUS_SRC_DIRS), $(OBJ_DIR)/$(notdir $(dir)))

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
