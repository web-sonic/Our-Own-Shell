/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 12:48:23 by sgath             #+#    #+#             */
/*   Updated: 2021/04/04 06:49:34 by ctragula         ###   ########.fr       */
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
# include "./gnl/get_next_line.h"
# include "./builtins/builtins.h"
# include "./parser/parser.h"
# include "./dlists/dlist.h"
# include "./libftplus/libftplus.h"

# define BUF_STR 5

int		g_error;

t_list	*split_cmdlst(char *line, int stop_symbol, t_list **magic_lst);
char	*readline(t_dlist **histlist, char *dir_add);
void	check_signal(char **rem_str, char *str);
int		running_term(struct termios *term);
void	control_flags_term(char *status, struct termios *term);
void	swap_argument_str(int direction, t_str *reader, t_dlist **histlist);
void	cmnd_d(t_str *reader, struct termios *term);
int		super_strlen(int start, char symbol, char *str);
void	line_split(t_env *arr_arg, char *line, int plus);
int		cmp_sort(t_env *cont, t_env *next);
char	*mod_address(char *dir_add);
void	*return_content(void *content);

void	free_env(void *env);
char	**getallenv(t_list *envlst);
void	signal_handler(int key);
t_cmd	*cmd_clear(t_cmd *cmd);
char	*ft_getenv(const char *name, t_list *envlst);
t_list	*get_cmds(char *line, t_list **magic_lst);
void	exec(t_list *cmd_lst, t_list *envlst, char *dir_add);
void	set_fds(t_fdstruct *fds, t_cmd *cmd, t_bool last_cmd);
void	init_fd(t_fdstruct *fds);
void	unset_fd(t_fdstruct *fds);
int		validate_redirects(t_cmd *cmd);
void	init_histlist(t_dlist **histlist, char *dir_add);
t_cmd	*init_cmd(void);
void	init_envlist(t_list **envlst, char **env);

#endif
