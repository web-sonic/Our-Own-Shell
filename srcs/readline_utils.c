/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:48:26 by sgath             #+#    #+#             */
/*   Updated: 2021/04/16 14:19:01 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	cmnd_d(t_str *reader, struct termios *term)
{
	if (!reader->rem_str || !ft_strncmp(reader->rem_str, "", 1))
	{
		ft_putstr_fd("exit\n", 1);
		dub_and_free(&reader->rem_str, "\n");
		tcsetattr(0, TCSANOW, term);
		exit(g_error);
	}
}

int
	running_term(struct termios *s_term)
{
	char			*temp_name;
	struct termios	term;

	temp_name = ft_strdup("xterm-256color");
	if (!temp_name)
		return (1);
	if (tcgetattr(0, &term) < 0)
		return (1);
	*s_term = term;
	term.c_lflag &= ~(ECHO | ICANON | ISIG);
	if (tcsetattr(0, TCSANOW, &term) < 0)
		return (1);
	tgetent(0, temp_name);
	free(temp_name);
	return (0);
}

static void
	swap_argument_str_up(char **rem_str, char **tmp_str, t_dlist **histlist)
{
	if (ft_dlstsize((*histlist)) != 0)
	{
		if (!(*tmp_str))
		{
			if (*rem_str)
				*tmp_str = ft_strdup(*rem_str);
			else
				*tmp_str = ft_calloc(sizeof(char), 1);
		}
		else if (ft_dlstsize((*histlist)->prev) != 0)
			*histlist = (*histlist)->prev;
		dub_and_free(rem_str, (*histlist)->content);
	}
	ft_putstr_fd(*rem_str, 1);
}

static void
	swap_argument_str_down(char **rem_str, char **tmp_str, t_dlist **histlist)
{
	if ((*histlist)->next)
	{
		*histlist = (*histlist)->next;
		dub_and_free(rem_str, (*histlist)->content);
	}
	else
	{
		if (!(*rem_str) || ft_strncmp(*rem_str, "", 1))
		{
			if (*tmp_str)
			{
				dub_and_free(rem_str, *tmp_str);
				free(*tmp_str);
				*tmp_str = 0;
			}
		}
		else if (*tmp_str != *rem_str)
			dub_and_free(rem_str, "");
	}
	ft_putstr_fd(*rem_str, 1);
}

void
	swap_argument_str(int direction, t_str *reader, t_dlist **histlist)
{
	if (!(*histlist))
		return ;
	tputs(restore_cursor, 1, ft_putchar);
	tputs(delete_line, 1, ft_putchar);
	ft_putstr_fd("minishell> ", 1);
	if (direction == 0)
		swap_argument_str_up(&reader->rem_str, &reader->tmp_str, histlist);
	else if (direction == 1)
		swap_argument_str_down(&reader->rem_str, &reader->tmp_str, histlist);
}
