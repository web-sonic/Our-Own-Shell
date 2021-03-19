/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 14:21:05 by sgath             #+#    #+#             */
/*   Updated: 2021/03/19 18:11:47 by sgath            ###   ########.fr       */
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
	swap_argument_str(char *str, char **rem_str)
{
	if (*rem_str)
		free(*rem_str);
	*rem_str = ft_strdup(str);
	tputs(restore_cursor, 1, ft_putchar);
	tputs(delete_line, 1, ft_putchar);
	tputs(tigetstr("ed"), 1, ft_putchar);
	ft_putstr_fd("./minishell> ", 1);
	ft_putstr_fd(str, 1);
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

	tputs(cursor_left, 1, ft_putchar);
	tputs(delete_character, 1, ft_putchar);
	len = ft_strlen(*rem_str);
	if (len - 1 >= 0)
		(*rem_str)[len - 1] = 0;
}

/* 
** @params: char *str: строка, которая принимает символы, введеные с консоли
**			char **rem_str: строка, хранящаяя символы введеные с консоли
** TODO: puts_line: Обрабатывает введеные в консоли или ранее введеные символы и
**					 выводит их на экран, и обрабатывает сигналы
*/
static void
	puts_line(char *str, char **rem_str)
{
	int i;

	i = read(0, str, 5);
	str[i] = 0;
	if (!ft_strncmp(str, "\e[A", 4))
		swap_argument_str("up", rem_str);
	else if (!ft_strncmp(str, "\e[B", 4))
		swap_argument_str("down", rem_str);
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
** @params: char *status: включение или отключение флагов
**			struct termios *term: Структура, содержашая в себе всю работу терминала
** TODO: control_flags_term: Включение или отключение флагов
*/
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

/* 
** @params: char **env: массив переменных окружения
** TODO: readline: Считывает введеные в консоль аргументы 
** @return сохраненные аргументы в виде строки
*/
char
	*readline(char **env)
{
	char	*str;
	char	*rem_str;
	char	*temp_name;
	struct	termios term;

	rem_str = 0;
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
	tputs(save_cursor, 1, ft_putchar);
	while(ft_strncmp(str, "\n", 2) && (ft_strncmp(str, "\13", 3)))
		puts_line(str, &rem_str);
	//ft_putendl_fd(rem_str, 1);
	free(str);
	return (rem_str);
}
