# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/06 13:45:21 by root              #+#    #+#              #
#    Updated: 2024/12/22 15:54:04 by yaharkat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = src/main.c src/utils/check_args.c src/utils/error.c src/utils/utils.c \
		src/init_struct.c src/parse_data.c src/check_data.c src/game/init_game.c

HEAD = -I includes -I Libft

OBJS = ${SRCS:.c=.o}

NAME = cub3D

CFLAGS = -Wall -Wextra -Werror -g3 $(HEAD) #-fsanitize=address

Includes = includes/cub3d.h \ Libft/libft.h \ minilibx-linux/mlx.h 

all : ${NAME}

${NAME} : ${OBJS} 
	make -C Libft
	make -C minilibx-linux
	cc ${OBJS} ${CFLAGS} -Lminilibx-linux -lmlx -L/usr/lib/X11 -lXext -lX11 -LLibft -lft -o ${NAME}

clean :
	make clean -C Libft
	make clean -C minilibx-linux
	rm -f ${OBJS}
fclean : clean
	make fclean -C Libft
	make clean -C minilibx-linux
	rm -f ${NAME}
re : fclean all clean

.SECONDARY: $(OBJS)
.PHONY: all clean fclean re