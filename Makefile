# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgath <sgath@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/16 15:29:48 by ctragula          #+#    #+#              #
#    Updated: 2021/03/19 17:56:32 by sgath            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	shell_loop.c \
		minishell.c \
		readline.c \
		signal.c \
		utils.c \
		./gnl/get_next_line.c \
		./gnl/get_next_line_utils.c \
		#parser/parser.c 

LIB =	libft/libft.a 

HEADERS =	minishell.h \
			./gnl/get_next_line.h \

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