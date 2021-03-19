/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:21:05 by sgath             #+#    #+#             */
/*   Updated: 2021/03/19 13:30:28 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <sys/ioctl.h>

int
	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

static void
	swap_argument_str(char *str)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(delete_line, 1, ft_putchar);
	//ft_putstr_fd(name, 1);
	tputs(tigetstr("ed"), 1, ft_putchar);
	ft_putchar_fd('#', 1);
	ft_putstr_fd(str, 1);
}

static void
	puts_line(char *str)
{
	int i;
	int n_bit;

//	iostl(0, FIONREAD, n_bit);
	i = read(0, str, 5);
	str[i] = 0;
	if (!ft_strncmp(str, "\e[A", 4))
		swap_argument_str("up");
	else if (!ft_strncmp(str, "\e[B", 4))
		swap_argument_str("down");
	else if (!ft_strncmp(str,"\177", 4))
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
	}
	//else if (!ft_strncmp(str, "\e[C", 4))
	//	return;
	else if(!ft_strncmp(str, "\04"))
		return();
	else
		write(1, str, i);
}

static void
	buf_str_check(char **str)
{
	char	*tmp;
	char	*empty_str;

	if (ft_strlen(*str) == BUF_STR)
	{
		tmp = *str;
		free(*str);
		empty_str = calloc(sizeof(char), BUF_STR);
		*str = ft_strjoin(tmp, empty_str);
		free(tmp);
		free(empty_str);
	}
}

void
	control_flags_term(char *status, struct termios *term)
{
	if (!ft_strncmp(status, "on", 3))
	{
		term->c_lflag &= ~ECHO;
		term->c_lflag &= ~ICANON;
		term->c_cflag &= ~ISIG;
	}
	else if (!ft_strncmp(status, "off", 4))
	{
		term->c_lflag |= ECHO;
		term->c_lflag |= ICANON;
		term->c_cflag |= ISIG;
	}
	else
		exit (1);
}

char
	*readline(char **env)
{
	char	*str;
	char	*temp_name;
	struct	termios term;

	temp_name = ft_strdup("xterm-256color");
	str = ft_calloc(sizeof(char), BUF_STR);
	if (!temp_name || !str)
		return (NULL);
	if (tcgetattr(0, &term) < 0)
		return(NULL);
	control_flags_term("on", &term);
	if (tcsetattr(0, TCSANOW, &term) < 0)
		return(NULL);
	tgetent(0, temp_name);
	//term.c_cc[VMIN] = 1;
	//term.c_cc[VTIME] = 0;
	tputs(save_cursor, 1, ft_putchar);
	while(ft_strncmp(str, "\n", 2) && (ft_strncmp(str, "\13", 3)))
	{
		buf_str_check(&str);
		puts_line(str);
	}
	return (str);
}
