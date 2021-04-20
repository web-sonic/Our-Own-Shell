# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/20 12:49:41 by sgath             #+#    #+#              #
#    Updated: 2021/04/20 13:18:55 by ctragula         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	./srcs/readline.c \
		./srcs/readline_utils.c \
		./srcs/minishell_utils.c \
		./srcs/init.c \
		./srcs/utils_env.c \
		./srcs/minishell.c \
		./srcs/signal_handler.c \
		./srcs/parser/cmd_list.c \
		./srcs/parser/parse_utils.c \
		./srcs/parser/parser.c \
		./srcs/parser/treates.c \
		./srcs/parser/parse_dollar.c \
		./srcs/parser/parse_fds.c \
		./srcs/execute/execute.c \
		./srcs/execute/fds.c \
		./srcs/execute/execute_utils.c \
		./srcs/dlists/ft_dlstclear.c \
		./srcs/dlists/ft_dlstadd_back.c \
		./srcs/dlists/ft_dlstnew.c \
		./srcs/dlists/ft_dlstsize.c \
		./srcs/gnl/get_next_line.c \
		./srcs/gnl/get_next_line_utils.c \
		./srcs/builtins/echo.c \
		./srcs/builtins/env.c \
		./srcs/builtins/exit.c \
		./srcs/builtins/pwd.c \
		./srcs/builtins/export.c \
		./srcs/builtins/unset.c \
		./srcs/builtins/cd.c \
		./srcs/builtins/export_utils.c \
		./srcs/errors/error_ft.c \
		./srcs/errors/error_flag.c \
		./srcs/errors/error_parser.c \
		./srcs/errors/exceptions.c \
		./srcs/libftplus/ft_strtolower.c \
		./srcs/libftplus/ft_dupfree.c \
		./srcs/libftplus/ft_ownrealloc.c \
		./srcs/libftplus/ft_putchar.c \
		./srcs/libftplus/ft_wordtab_realloc.c \
		./srcs/libftplus/ft_str_realloc.c \
		./srcs/libftplus/ft_isonlyprint.c \
		./srcs/libftplus/ft_digit.c \

LIB =	./srcs/libft/libft.a 

HEADERS =	./includes/minishell.h \
			./includes/structures.h \
			./srcs/parser/parser.h \
			./srcs/libftplus/libftplus.h \
			./srcs/gnl/get_next_line.h \
			./srcs/errors/errors.h \
			./srcs/dlists/dlist.h \
			./srcs/builtins/builtins.h \

NAME = minishell

CC = gcc -g -Wall -Wextra -Werror -ltermcap


FLAGS = -ltermcap  -L srcs/libft/ -lft

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(SRCS) $(HEADERS)
	$(MAKE) bonus -C srcs/libft
	$(CC) $(SRCS) $(FLAGS) -o $@

all: $(NAME)

clean:
	$(MAKE) clean -C srcs/libft

fclean:
	$(RM) $(NAME)
	$(MAKE) fclean -C srcs/libft

re: fclean all

wc:
	wc -l $(SRCS) $(HEADERS)

norme:
	norminetteV2 $(SRCS) $(HEADERS)

bonus:

.PHONY: all clean fclean re bonus
