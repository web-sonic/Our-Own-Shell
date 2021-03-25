/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 12:48:23 by sgath             #+#    #+#             */
/*   Updated: 2021/03/25 10:06:44 by ctragula         ###   ########.fr       */
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
# include "libft/libft.h"
# include "structures.h"
# include "errors.h"
# include "lexer.h"
# include "./gnl/get_next_line.h"
# include "lexer.h"

# define BUF_STR 5

t_list  *get_cmds(char *line);
char    *ft_ownrealloc(char *(*f)(const char *, const char *),
            char **s1, char *s2);
char	*ft_strldup(char *str, size_t len);
void	control_flags_term(char *status, struct termios *term);
int		running_term();
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
t_dlist	*ft_dlstnew(void *content);
int	    ft_dlstsize(t_dlist *lst);
char    *treat_str(char **str);
char    *treat_quotes(char **str, int quote);
t_list  *split_cmdlst(char *line, int stop_symbol);
t_dlist	*ft_dlstnew(void *content);
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
int	    ft_dlstsize(t_dlist *lst);
void	shell_loop(char *name, char **env, t_dlist **histlist);
char	*readline(t_dlist **histlist);
void	check_signal(char **rem_str, char *str);
int		running_term(struct termios *term);
void	control_flags_term(char *status, struct termios *term);
int		ft_putchar(int c);
void	write_new_symbol_str(char **rem_str, char *str);
void	dub_and_free(char **rem_str, char *str);
void	ft_echo(char **line);
int		ft_pwd(void);
void	ft_exit(long long *n,char **line);
void	ft_env(char **env);
char	*ft_strownjoin(char *dst, char *src);
char	*ft_strldup(char *str, size_t len);
char    *treat_str(char **str);
char    *treat_quotes(char **str, int quote);
t_list	*ft_parser(char *list);
t_list	*lexer(char *str);

#endif