# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaharkat <yaharkat@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/06 13:45:21 by root              #+#    #+#              #
#    Updated: 2025/01/05 22:22:11 by yaharkat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = building
NAME_BONUS = building_bonus

# Build rules
all: $(NAME)

$(NAME): man
	
man: $(NAME)
	@make -C mandatory
	@touch $(NAME)

bonus: $(NAME_BONUS)
	@make -C bonus
	@touch $(NAME_BONUS)

# Cleaning rules
clean:
	@make clean -C mandatory
	@make clean -C bonus
	@rm -f $(NAME) $(NAME_BONUS)
fclean:
	@make fclean -C mandatory
	@make fclean -C bonus
	@rm -f $(NAME) $(NAME_BONUS)
       
re: fclean all