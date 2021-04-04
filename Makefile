# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/20 12:49:41 by sgath             #+#    #+#              #
#    Updated: 2021/04/04 09:21:30 by ctragula         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	readline.c \
		readline_utils.c \
		minishell_utils.c \
		parser/cmd_list.c \
		parser/parse_utils.c \
		parser/parser.c \
		parser/treates.c \
		parser/parse_dollar.c \
		parser/parse_fds.c \
		execute/execute.c \
		execute/fds.c \
		./dlists/ft_dlstclear.c \
		./dlists/ft_dlstadd_back.c \
		./dlists/ft_dlstnew.c \
		./dlists/ft_dlstsize.c \
		./gnl/get_next_line.c \
		./gnl/get_next_line_utils.c \
		./builtins/echo.c \
		./builtins/env.c \
		./builtins/exit.c \
		./builtins/pwd.c \
		./builtins/export.c \
		./builtins/unset.c \
		./function/cd.c \
		./errors/error_ft.c \
		./errors/exceptions.c \
		./errors/error_parse.c \
		signal_handler.c \
		utils_env.c \
		minishell.c \
		libftplus/ft_strtolower.c \
		libftplus/ft_dupfree.c \
		libftplus/ft_ownrealloc.c \
		libftplus/ft_putchar.c \
		libftplus/ft_wordtab_realloc.c \
		libftplus/ft_str_realloc.c \
		init.c \
		#main_for_test.c \

LIB =	libft/libft.a 

HEADERS =	minishell.h \
			structures.h \
			parser/parser.h \
			libftplus/libftplus.h \
			gnl/get_next_line.h \
			errors/errors.h \
			dlists/dlist.h \
			builtins/builtins.h \

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
	$(MAKE) clean -C libft

fclean:
	$(RM) $(NAME)
	$(MAKE) fclean -C libft

re: fclean all

wc:
	wc -l $(SRCS) $(HEADERS)

norme:
	norminetteV2 $(SRCS) $(HEADERS)

bonus:

.PHONY: all clean fclean re bonus
