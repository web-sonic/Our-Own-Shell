# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/16 15:29:48 by ctragula          #+#    #+#              #
#    Updated: 2021/03/19 14:24:21 by ctragula         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	shell_loop.c \
		minishell.c \
		#parser/parser.c \
		#up_down.c

LIB = libft/libft.a

HEADERS = minishell.h

NAME = minishell

CC = gcc -g -Wall -Wextra

FLAGS = -ltermcap  -L libft/ -lft

.PHONY: all clean fclean re bonus

$(NAME): $(SRCS) $(HEADERS)
	$(MAKE) bonus -C libft
	$(CC) $(FLAGS) $(SRCS) -o $@

all: $(NAME)

clean:
	$(RM) *.o
	$(MAKE) clean -C libft

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) fclean -C libft

re: fclean all

bonus:

.PHONY: all clean fclean re bonus