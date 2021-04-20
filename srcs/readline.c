/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 12:50:25 by sgath             #+#    #+#             */
/*   Updated: 2021/04/20 09:25:07 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void
	delete_last_symbol_str(char **rem_str)
{
	int	len;

	if (!(*rem_str))
		return ;
	len = ft_strlen(*rem_str);
	if (len > 0)
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_line, 1, ft_putchar);
		ft_putstr_fd("minishell> ", 1);
		(*rem_str)[len - 1] = 0;
		ft_putstr_fd(*rem_str, 1);
	}
}

static int
	check_norm_print(t_str *reader)
{
	if (!ft_strncmp(reader->line_term, "\e[C", 4) ||
	!ft_strncmp(reader->line_term, "\e[D", 4) ||
	!ft_strncmp(reader->line_term, "\x1c", 4))
		return (1);
	if (!ft_strncmp(reader->line_term, "\t", 3) ||
	!ft_strncmp(reader->line_term, "\f", 3))
		return (1);
	if (!ft_strncmp(reader->line_term, "\v", 3) ||
	!ft_strncmp(reader->line_term, "\13", 4))
		return (1);
	if (!ft_strncmp(reader->line_term, "\033[1;2", 6) ||
	!ft_strncmp(reader->line_term, "\033[3;2", 6))
		return (1);
	return (0);
}

static void
	puts_line(t_str *reader, t_dlist **histlist, struct termios	*term)
{
	int	i;

	i = read(0, reader->line_term, 5);
	reader->line_term[i] = 0;
	if (!ft_strncmp(reader->line_term, "\e[A", 4))
		swap_argument_str(0, reader, histlist);
	else if (!ft_strncmp(reader->line_term, "\e[B", 4))
		swap_argument_str(1, reader, histlist);
	else if (!ft_strncmp(reader->line_term, "\177", 4) ||
		!ft_strncmp(reader->line_term, "\b", 3))
		delete_last_symbol_str(&reader->rem_str);
	else if (!ft_strncmp(reader->line_term, "\4", 3))
		cmnd_d(reader, term);
	else if (check_norm_print(reader) == 1)
		reader->line_term[0] = 0;
	else
	{
		write_new_symbol_str(&reader->rem_str, reader->line_term);
		write(1, reader->line_term, i);
	}
}

void
	end_readline(t_dlist **histlist, t_str *reader, char *dir_add)
{
	int	fd;

	if (reader->rem_str)
		(reader->rem_str)[ft_strlen(reader->rem_str) - 1] = '\0';
	if (!ft_strncmp(reader->line_term, "\3", 3))
	{
		if (reader->rem_str)
			free(reader->rem_str);
		reader->rem_str = NULL;
		ft_putchar_fd('\n', 1);
		g_struct.error = 1;
	}
	if (reader->rem_str && (reader->rem_str)[0] != '\n' &&
		(reader->rem_str)[0] != '\0')
	{
		ft_dlstadd_back(histlist, ft_dlstnew(reader->rem_str));
		fd = open(dir_add, O_WRONLY | O_APPEND);
		ft_putendl_fd(reader->rem_str, fd);
		close(fd);
	}
	if (reader->tmp_str)
		free(reader->tmp_str);
	free(reader->line_term);
}

char
	*readline(t_dlist **histlist, char *dir_add)
{
	t_str			reader;
	struct termios	term;

	reader.rem_str = NULL;
	reader.tmp_str = NULL;
	reader.line_term = ft_calloc(sizeof(char), BUF_STR);
	if (!reader.line_term || running_term(&term) != 0)
		return (NULL);
	tputs(save_cursor, 1, ft_putchar);
	ft_putstr_fd("minishell> ", 1);
	while (ft_strncmp(reader.line_term, "\n", 2) &&
	(ft_strncmp(reader.line_term, "\13", 3)) &&
	(ft_strncmp(reader.line_term, "\3", 3)))
		puts_line(&reader, histlist, &term);
	end_readline(histlist, &reader, dir_add);
	tcsetattr(0, TCSANOW, &term);
	return (reader.rem_str);
}
