/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 14:02:48 by sgath             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/03/19 18:17:59 by sgath            ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2021/03/19 16:18:16 by ctragula         ###   ########.fr       */
=======
/*   Updated: 2021/03/19 17:54:44 by sgath            ###   ########.fr       */
>>>>>>> 50d6066a64f8c366e05019ce4cb3e6e24a7eb750
>>>>>>> dfe041e880375344b446bf06b587cd5ca3cb8361
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
<<<<<<< HEAD
=======
<<<<<<< HEAD
# include "lexer.h"
=======
# include "./gnl/get_next_line.h"
>>>>>>> 50d6066a64f8c366e05019ce4cb3e6e24a7eb750
>>>>>>> dfe041e880375344b446bf06b587cd5ca3cb8361

# define BUF_STR 5

void	shell_loop(char *name, char **env);
char	*readline(char **env);
void	check_signal(char **rem_str, char *str);
int		ft_putchar(int c);

#endif