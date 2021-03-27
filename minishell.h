/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 12:48:23 by sgath             #+#    #+#             */
/*   Updated: 2021/03/27 17:25:15 by sgath            ###   ########.fr       */
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
# include "errors.h"
# include "lexer.h"
# include "./gnl/get_next_line.h"

# define BUF_STR 5

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
t_dlist	*ft_dlstnew(void *content);
int	    ft_dlstsize(t_dlist *lst);
void	ft_dlstclear(t_dlist **lst, void (*del)(void*));

t_list  *get_cmds(char *line);
char    *ft_ownrealloc(char *(*f)(const char *, const char *),
            char **s1, char *s2);
char	*ft_strldup(char *str, size_t len);
char    *treat_str(char **str);
char    *treat_quotes(char **str, int quote);
t_list  *split_cmdlst(char *line, int stop_symbol);
char	*ft_strldup(char *str, size_t len);
char    *treat_str(char **str);
char    *treat_quotes(char **str, int quote);
int     error_parse(char *str, int c);

char	*readline(t_dlist **histlist, char *dir_add);
void	check_signal(char **rem_str, char *str);
int		running_term(struct termios *term);
void	control_flags_term(char *status, struct termios *term);
int		ft_putchar(int c);
void	write_new_symbol_str(char **rem_str, char *str);
void	dub_and_free(char **rem_str, char *str);
void	swap_argument_str(int direction, t_str *reader, t_dlist **histlist);
void	cmnd_d(t_str *reader, struct termios *term);
int		super_strlen(int start, char symbol, char *str);

void	ft_echo(char **line);
int		ft_pwd(void);
void	ft_exit(long long *n,char **line);
void	ft_env(t_list *envlst);
//void	ft_export(char **line);
void	ft_unset(char **line, t_list *envlst);

void	execute(t_list *cmd_lst, char **env);
t_cmd	parse_complete(char *str, char **env);

#endif