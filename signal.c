/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:48:26 by sgath             #+#    #+#             */
/*   Updated: 2021/03/28 15:23:15 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
** @params: t_str *reader: структура со строками, нужными для записи в листы
**			struct termios *term: стандартные настройки терминала
** TODO: cmnd_d: завершает работу с минишелом, если строка пустая
*/
void
	cmnd_d(t_str *reader, struct termios *term)
{
	if (!reader->rem_str || !ft_strncmp(reader->rem_str, "", 1))
	{
		ft_putstr_fd("exit\n", 1);
		dub_and_free(&reader->rem_str, "\n");
		tcsetattr(0,  TCSANOW, term);
		exit(0);
	}
}

/*
** @params: struct termios *s_term:
** TODO: running_term: измение параметров терминала
** @return : 0 - если изменения терминала прошло успешно
**			 1 - если при изменении терминала произошла ошибка
*/
int
	running_term(struct termios *s_term)
{
	char	*temp_name;
	struct termios term;

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

/* 
** @params: char **rem_str: строка, хранящаяя символы введеные с консоли
**			char **tmp_str: строка для временного хранения не записонной строки в лист
**			char **histlist: листы с командами
** TODO: swap_argument_str_up: заменяет одну строку на другую
*/
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

/*
** @params: char **rem_str: строка, хранящаяя символы введеные с консоли
**			char **tmp_str: строка для временного хранения не записонной строки в лист
**			t_dlist **histlist: листы с командами
** TODO: swap_argument_str_down: заменяет одну строку на другую
*/
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
		if	(!(*rem_str) || ft_strncmp(*rem_str, "", 1))
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

/* 
** @params: int direction: направление стрелочек: 0 вверх, 1 вниз
**			t_str *reader: структура со строками, нужными для записи в листы
**			t_dlist **histlist: листы с командами
** TODO: swap_argument_str_down: заменяет одну строку на другую
*/
void
	swap_argument_str(int direction, t_str *reader, t_dlist **histlist)
{
	if (!(*histlist))
		return;

	tputs(restore_cursor, 1, ft_putchar);
	tputs(delete_line, 1, ft_putchar);
	//tputs(tigetstr("ed"), 1, ft_putchar);
	ft_putstr_fd("minishell> ", 1);

	if (direction == 0)
		swap_argument_str_up(&reader->rem_str, &reader->tmp_str, histlist);
	else if (direction ==1)
		swap_argument_str_down(&reader->rem_str, &reader->tmp_str, histlist);
}