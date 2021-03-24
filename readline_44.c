/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 12:50:25 by sgath             #+#    #+#             */
/*   Updated: 2021/03/23 17:04:03 by sgath            ###   ########.fr       */
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
	swap_argument_str(int direction, char **rem_str, char **tmp_str, t_dlist **histlist)
{
	if (!(*histlist))
		return;

	tputs(restore_cursor, 1, ft_putchar);
	tputs(delete_line, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	ft_putstr_fd("minishell> ", 1);
	if (direction == 0)
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
				// if (!(*tmp_str))
				// {
				// 	if (*rem_str)
				// 		*tmp_str = *rem_str;
				// 	else
				// 		*tmp_str = "";
				// }
			dub_and_free(rem_str, (*histlist)->content);
			//*rem_str = ft_strdup((*histlist)->content);
		}

	}
	if(direction == 1)
	{
		if ((*histlist)->next)
		{
			*histlist = (*histlist)->next;
			dub_and_free(rem_str, (*histlist)->content);
			//*rem_str = ft_strdup((*histlist)->content);
		}
		else
		{
			if	(!(*rem_str) || ft_strncmp(*rem_str, "", 1))
			{
				if (*tmp_str)
				{
					dub_and_free(rem_str, *tmp_str);
					//*rem_str = ft_strdup((*tmp_str));
					free(*tmp_str);
					*tmp_str = 0;
				}
			}
			else if (*tmp_str != *rem_str)
				dub_and_free(rem_str, "");
				//*rem_str = ft_strdup("");
		}
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
		//tputs(cursor_right, 1, ft_putchar);
		// tputs(delete_character, 1, ft_putchar);
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
** TODO: puts_line: Обрабатывает введеные в консоли или ранее введеные символы и
**					 выводит их на экран, и обрабатывает сигналы
*/
static void
	puts_line(char *str, char **rem_str, char **tmp_str, t_dlist **histlist)
{
	int i;

	i = read(0, str, 5);
	str[i] = 0;
	if (!ft_strncmp(str, "\e[A", 4))
		swap_argument_str(0, rem_str, tmp_str, histlist);
	else if (!ft_strncmp(str, "\e[B", 4))
		swap_argument_str(1, rem_str, tmp_str, histlist);
	else if (!ft_strncmp(str,"\177", 4))
		delete_last_symbol_str(rem_str);
	else if (!ft_strncmp(str, "\e[C", 4) || !ft_strncmp(str, "\e[D", 4) )
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
	char	*tmp_str;

	rem_str = 0;
	tmp_str = 0;
	str = ft_calloc(sizeof(char), BUF_STR);
	if (!str || running_term() != 0)
		return (NULL);
	tputs(save_cursor, 1, ft_putchar);
	while(ft_strncmp(str, "\n", 2) && (ft_strncmp(str, "\13", 3)))
		puts_line(str, &rem_str, &tmp_str, histlist);
	if (ft_strncmp(rem_str, "", 1))
		ft_dlstadd_back(histlist, ft_dlstnew(rem_str));
	free(str);
	if (tmp_str)
		free(tmp_str);
	
	return (rem_str);
}
