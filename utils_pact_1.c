/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pact_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:15:21 by sgath             #+#    #+#             */
/*   Updated: 2021/03/25 12:35:04 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

char
	*ft_strldup(char *str, size_t len)
{
	char	*dst;

	dst = ft_calloc(len, sizeof(char));
	ft_strlcpy(dst, str, len);
	dst[len] = 0;
	return (dst);
}

char
	*ft_ownrealloc(char *(*f)(const char *, const char *), char **s1, char *s2)
{
	char	*tmp_str;

	tmp_str = f(*s1, s2);
	free(*s1);
	return (tmp_str);
}

/*
** @params: char *status: включение или отключение флагов
**			struct termios *term: Структура, содержашая в себе всю работу
** терминала
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
		exit(1);
}

/*
** @params: void
** TODO: running_term: измение параметров терминала
** @return : 0 - если изменения терминала прошло успешно
**			 1 - если при изменении терминала произошла ошибка
*/
int
	running_term(struct termios *term)
{
	char	*temp_name;

	temp_name = ft_strdup("xterm-256color");
	if (!temp_name)
		return (1);
	if (tcgetattr(0, term) < 0)
		return (1);
	control_flags_term("on", term);
	if (tcsetattr(0, TCSANOW, term) < 0)
		return (1);
	tgetent(0, temp_name);
	free(temp_name);
	return (0);
}
