# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/20 12:49:41 by sgath             #+#    #+#              #
#    Updated: 2021/03/24 11:13:21 by ctragula         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	minishell.c \
		readline.c \
		signal.c \
<<<<<<< HEAD
		utils.c \
		utils_pact_1.c \
		utils_pact_2.c \
		parser/cmd_list.c \
=======
		utils_pact_1.c \
		utils_pact_2.c \
		parser/parser.c \
		parser/lexer.c \
>>>>>>> 8c91cbe1b97dda9043629b6cd89e3f3fc5158866
		dlists/ft_dlstadd_back.c \
		dlists/ft_dlstnew.c \
		dlists/ft_dlstsize.c \
		./gnl/get_next_line.c \
		./gnl/get_next_line_utils.c \

LIB =	libft/libft.a 

HEADERS =	minishell.h \

NAME = minishell

CC = gcc -g -Wall -Wextra
#-Werror

FLAGS = -ltermcap  -L libft/ -lft

.PHONY: all clean fclean re bonus

all: $(NAME)

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