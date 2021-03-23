/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 12:48:23 by sgath             #+#    #+#             */
/*   Updated: 2021/03/23 12:14:16 by ctragula         ###   ########.fr       */
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
# include "libft/libft.h"
# include "structures.h"
# include "errors.h"
# include "lexer.h"
# include "./gnl/get_next_line.h"
# include "lexer.h"

# define BUF_STR 5

void	shell_loop(char *name, char **env, t_dlist **histlist);
char	*readline(t_dlist **histlist);
void	check_signal(char **rem_str, char *str);
int		ft_putchar(int c);
t_list	*ft_parser(char *list);
char	*ft_strownjoin(char *dst, char *src);
char	*ft_strldup(char *str, size_t len);
t_list	*lexer(char *str);
void	control_flags_term(char *status, struct termios *term);
int		running_term();
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
t_dlist	*ft_dlstnew(void *content);
int	    ft_dlstsize(t_dlist *lst);
char    *treat_str(char **str);
char    *treat_quotes(char **str, int quote);

#endif