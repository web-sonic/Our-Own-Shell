/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:48:26 by sgath             #+#    #+#             */
/*   Updated: 2021/03/26 15:50:20 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
