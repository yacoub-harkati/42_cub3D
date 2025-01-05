# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzarhoun <rzarhoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/06 13:45:21 by root              #+#    #+#              #
#    Updated: 2025/01/05 23:05:25 by rzarhoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = building

# Build rules
all: $(NAME)

$(NAME): mandatory
	
mandatory:
	@make -C mandatory

bonus:
	@make -C bonus

# Cleaning rules
clean:
	@make clean -C mandatory
	@make clean -C bonus
fclean:
	@make fclean -C mandatory
	@make fclean -C bonus
       
re: fclean all
.PHONY: bonus mandatory all clean fclean re