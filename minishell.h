/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:02:48 by sgath             #+#    #+#             */
/*   Updated: 2021/03/19 18:17:40 by ctragula         ###   ########.fr       */
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

# define BUF_STR 5
# define SYMBOL_LEN 2

void	shell_loop(char *name, char **env);
char	*readline(char **env);
void	check_signal(char **rem_str, char *str);
int		ft_putchar(int c);

#endif