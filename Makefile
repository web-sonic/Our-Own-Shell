# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgath <sgath@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/16 15:29:48 by ctragula          #+#    #+#              #
#    Updated: 2021/03/16 18:11:58 by sgath            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = up_dowd.c 


HEADERS = minishell.h

NAME = minishell

CFLAGS = -g -c -Wall -Wextra -Werror -ltermcap

.PHONY: all clean fclean re bonus

$(NAME): $(SRC) $(HEADERS)
	$(MAKE) bonus -C libft
	gcc $(FLG) -L libft/ -lft $(FLC) -o $(NAME)

clean:
	$(RM) *.o *.d
	$(MAKE) clean -C libft

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) fclean -C libft

re: fclean all

bonus: