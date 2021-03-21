# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgath <sgath@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/20 12:49:41 by sgath             #+#    #+#              #
#    Updated: 2021/03/21 12:34:47 by sgath            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	minishell.c \
		readline.c \
		signal.c \
		utils.c \
		./gnl/get_next_line.c \
		./gnl/get_next_line_utils.c \
		parser/parser.c \
		parser/lexer.c \
		dlists/ft_dlstadd_back.c \
		dlists/ft_dlstnew.c \
		dlists/ft_dlstsize.c 

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