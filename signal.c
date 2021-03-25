/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:48:26 by sgath             #+#    #+#             */
/*   Updated: 2021/03/25 16:59:57 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	check_signal(char **rem_str, char *str)
{
	if(!ft_strncmp(str, "\4", 2) && !(*rem_str))
	{
		ft_putstr_fd("\nminishell> exit\n", 1);
		exit(0);
	}
	else if (!ft_strncmp(str, "\3", 2))
	{
		ft_putstr_fd("\nminishell> ", 1);
	}
}

/*
** @params: void
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
