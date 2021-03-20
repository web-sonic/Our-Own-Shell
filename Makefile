# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/16 15:29:48 by ctragula          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2021/03/19 18:17:52 by sgath            ###   ########.fr        #
=======
#    Updated: 2021/03/20 09:24:56 by ctragula         ###   ########.fr        #
>>>>>>> 5a37a3fc5134946a0ed2079a9dbfe0e20421c0be
#                                                                              #
# **************************************************************************** #

SRCS =	shell_loop.c \
		minishell.c \
		readline.c \
		signal.c \
		utils.c \
<<<<<<< HEAD

		#parser/parser.c 
=======
		./gnl/get_next_line.c \
		./gnl/get_next_line_utils.c \
		parser/parser.c 
>>>>>>> 5a37a3fc5134946a0ed2079a9dbfe0e20421c0be

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