# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/06 13:45:21 by root              #+#    #+#              #
#    Updated: 2025/01/05 23:09:17 by rzarhoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = cub3D

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -ffast-math
SANITIZE = -fsanitize=address -g3

# Libraries
MLX_DIR = minilibx-linux
MLX_LIB = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11
LIBFT_DIR = Libft
LIBFT = -L$(LIBFT_DIR) -lft
MATH_LIB = -lm

# Include directories
INCLUDES = -I includes -I $(LIBFT_DIR)

# Source files
SRC_DIR = src
UTILS_DIR = $(SRC_DIR)/utils
RAYCAST_DIR = $(SRC_DIR)/raycasting

SRCS = $(SRC_DIR)/main_bonus.c \
       $(UTILS_DIR)/check_args_bonus.c \
       $(UTILS_DIR)/error_bonus.c \
       $(UTILS_DIR)/utils1_bonus.c \
       $(UTILS_DIR)/utils2_bonus.c \
       $(UTILS_DIR)/logic_bonus.c \
       $(UTILS_DIR)/raycasting_utils_bonus.c \
       $(SRC_DIR)/init_struct_bonus.c \
       $(SRC_DIR)/door_handler_bonus.c \
       $(SRC_DIR)/parse_data_bonus.c \
       $(SRC_DIR)/check_file_bonus.c \
       $(SRC_DIR)/check_map_bonus.c \
       $(SRC_DIR)/check_walls_bonus.c \
       $(SRC_DIR)/check_utils_bonus.c \
       $(SRC_DIR)/game_loop_bonus.c \
       $(SRC_DIR)/player_move_bonus.c \
       $(SRC_DIR)/mouse_control_bonus.c \
       $(SRC_DIR)/door_utils_bonus.c \
       $(SRC_DIR)/game_init_bonus.c \
       $(SRC_DIR)/game_cleanup_bonus.c \
       $(RAYCAST_DIR)/render_bonus.c \
       $(RAYCAST_DIR)/init_ray_bonus.c \
       $(RAYCAST_DIR)/render_door_bonus.c \
       $(RAYCAST_DIR)/calc_bonus.c \
       $(RAYCAST_DIR)/door_dda_bonus.c \
       $(RAYCAST_DIR)/walls_dda_bonus.c \
       $(RAYCAST_DIR)/cast_rays_bonus.c \
       $(RAYCAST_DIR)/draw_map_bonus.c \
       $(RAYCAST_DIR)/draw_map_utils_bonus.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = includes/cub3d.h \
          $(LIBFT_DIR)/libft.h \
          $(MLX_DIR)/mlx.h

# Build rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "Building dependencies..."
	@make -C $(LIBFT_DIR)
	@echo "Linking $(NAME)..."
	@$(CC) $(OBJS) $(CFLAGS) $(MLX_LIB) $(LIBFT) $(MATH_LIB) -o $(NAME)
	@echo "Build complete!"

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Cleaning rules
clean:
	@echo "Cleaning object files..."
	@make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)
	@echo "Clean complete!"

fclean: clean
	@echo "Cleaning executable and libraries..."
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)
	@echo "Full clean complete!"

re: fclean all

# Development rules
dev: CFLAGS += $(SANITIZE)
dev: re

# Phony targets
.PHONY: all clean fclean re dev
.SECONDARY: $(OBJS)