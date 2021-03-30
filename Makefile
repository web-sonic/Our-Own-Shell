# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/20 12:49:41 by sgath             #+#    #+#              #
#    Updated: 2021/03/30 20:02:32 by ctragula         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	minishell.c \
		readline.c \
		signal.c \
		utils_pact_1.c \
		utils_pact_2.c \
		parser/cmd_list.c \
		parser/error_parse.c \
		execute/execute.c \
		parser/parser.c \
		./dlists/ft_dlstclear.c \
		./dlists/ft_dlstadd_back.c \
		./dlists/ft_dlstnew.c \
		./dlists/ft_dlstsize.c \
		./gnl/get_next_line.c \
		./gnl/get_next_line_utils.c \
		./function/echo.c \
		./function/env.c \
		./function/exit.c \
		./function/pwd.c \
		./function/export.c \
		./function/cd.c \
		getallenv.c \
		#./function/unset.c \

LIB =	libft/libft.a 

HEADERS =	minishell.h \

NAME = minishell

CC = gcc -g -Wall -Wextra -ltermcap
#-Werror

FLAGS = -ltermcap  -L libft/ -lft

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(MAKE) bonus -C libft
	$(CC) $(SRCS) $(FLAGS) -o $@

all: $(NAME)

clean:
	$(RM) *.o
	$(MAKE) clean -C libft

fclean:	clean
	$(RM) $(NAME)
	$(MAKE) fclean -C libft

re: fclean all

wc:
	wc -l $(SRCS)

bonus:

.PHONY: all clean fclean re bonus