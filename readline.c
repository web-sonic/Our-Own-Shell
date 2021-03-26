/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 12:50:25 by sgath             #+#    #+#             */
/*   Updated: 2021/03/26 15:49:26 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

/* 
** @params: char **rem_str: строка, хранящаяя символы введеные с консоли
**			char **tmp_str: строка для временного хранения не записонной строки в лист
**			char **histlist: листы с командами
** TODO: swap_argument_str_up: заменяет одну строку на другую
*/
static void
	swap_argument_str_up(char **rem_str, char **tmp_str, t_dlist **histlist)
{
	if (!(*histlist))
		return;

	tputs(restore_cursor, 1, ft_putchar);
	tputs(delete_line, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	ft_putstr_fd("minishell> ", 1);

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
**			char **histlist: листы с командами
** TODO: swap_argument_str_down: заменяет одну строку на другую
*/
static void
	swap_argument_str_down(char **rem_str, char **tmp_str, t_dlist **histlist)
{
	if (!(*histlist))
		return;

	tputs(restore_cursor, 1, ft_putchar);
	tputs(delete_line, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	ft_putstr_fd("minishell> ", 1);

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
** @params: char **rem_str: строка, хранящаяя символы введеные с консоли
** TODO: delete_last_symbol_str: удаляет последный символ, имитирует работу backspase
*/
static void
	delete_last_symbol_str(char **rem_str)
{
	int len;
	if (!(*rem_str))
		return;
	len = ft_strlen(*rem_str);
	if (len > 0)
	{
		tputs(restore_cursor, 1, ft_putchar);
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_line, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		ft_putstr_fd("minishell> ", 1);
		(*rem_str)[len - 1] = 0;
		ft_putstr_fd(*rem_str, 1);
	}
}

/* 
** @params: char *str: строка, которая принимает символы, введеные с консоли
**			char **rem_str: строка, хранящаяя символы введеные с консоли
**			char **tmp_str: строка для временного хранения не записонной строки в лист
**			char **histlist: листы с командами
** TODO: puts_line: Обрабатывает введеные в консоли или ранее введеные символы и
**					 выводит их на экран, и обрабатывает сигналы
*/
static void
	puts_line(t_str *reader, t_dlist **histlist, struct termios	*term)
{
	int i;

	i = read(0, reader->line_term, 5);
	reader->line_term[i] = 0;
	if (!ft_strncmp(reader->line_term, "\e[A", 4))
		swap_argument_str_up(&reader->rem_str, &reader->tmp_str, histlist);
	else if (!ft_strncmp(reader->line_term, "\e[B", 4))
		swap_argument_str_down(&reader->rem_str, &reader->tmp_str, histlist);
	else if (!ft_strncmp(reader->line_term,"\177", 4))
		delete_last_symbol_str(&reader->rem_str);
	else if (!ft_strncmp(reader->line_term, "\e[C", 4) || !ft_strncmp(reader->line_term, "\e[D", 4) )
		return;
	else if (!ft_strncmp(reader->line_term, "\4", 2))
	
	else
	{
		write_new_symbol_str(&reader->rem_str, reader->line_term);
		write(1, reader->line_term, i);
	}
}

void
	end_readline(t_dlist **histlist, t_str *reader, char *dir_add)
{
	int fd;

	if (reader->rem_str && (reader->rem_str)[0] != '\n' && (reader->rem_str)[0] != '\0')
	{
		(reader->rem_str)[ft_strlen(reader->rem_str) - 1] = '\0';
		if (!ft_strncmp(reader->line_term, "\3", 3))
			ft_putchar_fd('\n', 1);
		else
		{
			ft_dlstadd_back(histlist, ft_dlstnew(reader->rem_str));
			fd = open(dir_add, O_WRONLY | O_APPEND);
			ft_putendl_fd(reader->rem_str, fd);
			close(fd);
		}
	}
	if (reader->tmp_str)
		free(reader->tmp_str);
	free(reader->line_term);
}

/* 
** @params: char **env: массив переменных окружения
** TODO: readline: Считывает введеные в консоль аргументы 
** @return сохраненные аргументы в виде строки
*/
char
	*readline(t_dlist **histlist, char *dir_add)
{
	t_str			reader;
	struct termios	term;

	reader.rem_str = 0;
	reader.tmp_str = 0;
	reader.line_term = ft_calloc(sizeof(char), BUF_STR);
	if (!reader.line_term || running_term(&term) != 0)
		return (NULL);
	tputs(save_cursor, 1, ft_putchar);
	while(ft_strncmp(reader.line_term, "\n", 2) && (ft_strncmp(reader.line_term, "\13", 3)) && (ft_strncmp(reader.line_term, "\3", 3)))
		puts_line(&reader, histlist, &term);
	end_readline(histlist, &reader, dir_add);
	tcsetattr(0,  TCSANOW, &term);
	return (reader.rem_str);
}
