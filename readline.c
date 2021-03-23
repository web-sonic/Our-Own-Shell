/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 12:50:25 by sgath             #+#    #+#             */
/*   Updated: 2021/03/21 13:57:36 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

/* 
** @params: char *str:строка, которая принимает символы, введеные с консоли
**			char **rem_str: строка, хранящаяя символы введеные с консоли
** TODO: swap_argument_str: заменяет одну строку на другую
*/
static void
	swap_argument_str(char *str, char **rem_str, t_dlist **histlist)
{
	char *tmp;

	tmp = 0;
	if (!(*histlist))
		return;
	tputs(restore_cursor, 1, ft_putchar);
	tputs(delete_line, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	ft_putstr_fd("minishell> ", 1);
	if (!ft_strncmp(str, "up", 3))
	{
		if((*histlist)->prev && ft_dlstsize((*histlist)->prev) != 0)
		{
			*histlist = (*histlist)->prev;
			tmp = (*histlist)->content;
		}
		else
			tmp = *rem_str;
	}
	else if(!ft_strncmp(str, "down", 5))
	{
		if ((*histlist)->next)
		{
			*histlist = (*histlist)->next;
			tmp = (*histlist)->content;
		}
		else
			tmp = *rem_str;
	}
	ft_putstr_fd(tmp, 1);
}

/* 
** @params: char *str: строка, которая принимает символы, введеные с консоли
**			char **rem_str: строка, хранящаяя символы введеные с консоли
** TODO: write_new_symbol_str: Посимвольно добавляет к rem_str введенные в консоль символы
*/
static void
	write_new_symbol_str(char **rem_str, char *str)
{
	char *tmp;

	if (!(*rem_str))
		*rem_str = ft_strdup(str);
	else
	{
		tmp = ft_strjoin(*rem_str, str);
		free(*rem_str);
		*rem_str = tmp;
		//free(tmp);
	}
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
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
		(*rem_str)[len - 1] = 0;
	}
}

/* 
** @params: char *str: строка, которая принимает символы, введеные с консоли
**			char **rem_str: строка, хранящаяя символы введеные с консоли
** TODO: puts_line: Обрабатывает введеные в консоли или ранее введеные символы и
**					 выводит их на экран, и обрабатывает сигналы
*/
static void
	puts_line(char *str, char **rem_str, t_dlist **histlist)
{
	int i;

	i = read(0, str, 5);
	str[i] = 0;
	if (!ft_strncmp(str, "\e[A", 4))
		swap_argument_str("up", rem_str, histlist);
	else if (!ft_strncmp(str, "\e[B", 4))
		swap_argument_str("down", rem_str, histlist);
	else if (!ft_strncmp(str,"\177", 4))
		delete_last_symbol_str(rem_str);
	else if (!ft_strncmp(str, "\e[C", 4))
		return;
	else if (!ft_strncmp(str, "\4", 2) || !ft_strncmp(str, "\3", 2))
		check_signal(rem_str, str);
	else
	{
		write_new_symbol_str(rem_str, str);
		write(1, str, i);
	}
}



/* 
** @params: char **env: массив переменных окружения
** TODO: readline: Считывает введеные в консоль аргументы 
** @return сохраненные аргументы в виде строки
*/
char
	*readline(t_dlist **histlist)
{
	char	*str;
	char	*rem_str;

	rem_str = 0;
	str = ft_calloc(sizeof(char), BUF_STR);
	if (!str || running_term() != 0)
		return (NULL);
	tputs(save_cursor, 1, ft_putchar);
	while(ft_strncmp(str, "\n", 2) && (ft_strncmp(str, "\13", 3)))
		puts_line(str, &rem_str, histlist);
	//ft_putendl_fd(rem_str, 1);
	ft_dlstadd_back(histlist, ft_dlstnew(rem_str));
	free(str);
	return (rem_str);
}
