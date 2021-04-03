/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 12:48:23 by sgath             #+#    #+#             */
/*   Updated: 2021/04/03 09:43:47 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <sys/errno.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <limits.h>
# include <string.h>
# include "./libft/libft.h"
# include "structures.h"
# include "./errors/errors.h"
# include "lexer.h"
# include "./gnl/get_next_line.h"
# include "./function/function.h"

# define BUF_STR 5

int		g_error;

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
t_dlist	*ft_dlstnew(void *content);
int	    ft_dlstsize(t_dlist *lst);
void	ft_dlstclear(t_dlist **lst, void (*del)(void*));

t_list  *get_cmds(char *line, t_list **magic_lst);
char    *ft_ownrealloc(char *(*f)(const char *, const char *),
			char **s1, char *s2);
char    *treat_str(char **str);
char    *treat_quotes(char **str, int quote, char *dir_addr);
t_list  *split_cmdlst(char *line, int stop_symbol, t_list **magic_lst);
char    *treat_str(char **str);
char	**ft_wordtab_realloc(char **wordtab, char *str);
t_list  *error_parse(char *str, int c);
void	file_error(char *file, char *error);

char	*readline(t_dlist **histlist, char *dir_add);
void	check_signal(char **rem_str, char *str);
int		running_term(struct termios *term);
void	control_flags_term(char *status, struct termios *term);
int		ft_putchar(int c);
void	write_new_symbol_str(char **rem_str, char *str);
int		dub_and_free(char **rem_str, char *str);
void	swap_argument_str(int direction, t_str *reader, t_dlist **histlist);
void	cmnd_d(t_str *reader, struct termios *term);
int		super_strlen(int start, char symbol, char *str);
char	*ft_getenv(const char *name, t_list *envlst);
void	line_split(t_env *arr_arg, char *line);
int		cmp_sort(t_env *cont, t_env *next);
char	*mod_address(char *dir_add);

void	*return_content(void *content);
void	free_env(void *env);
void	line_split(t_env *arr_arg, char *line);

void    execute(t_list *cmd_lst, t_list *envlst, char *dir_add);
t_cmd	*parser(char *str, t_list *envlst, char *dir_addr);
char    *parse_token(char **str, char *dir_addr);
char	**getallenv(t_list *envlst);
void	signal_handler(int key);
t_cmd	*cmd_clear(t_cmd *cmd);
void	skip_spaces(char **str, char *spaces);
char	*goto_stopsymbol(char **str, char stop_symbol, t_bool is_quote);

#endif
