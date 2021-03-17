/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_dowd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:45:42 by sgath             #+#    #+#             */
/*   Updated: 2021/03/16 18:08:37 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

int
	main(int argc, char **argv, char const **envp)
{
	struct	termios term;
	char			*str;
	int				i;

	str = calloc(sizeof(char), 2001);
	if (!str)
		return(0);
	tcgetattr(0, &term);
	//term.c_lflag &
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	term.c_cc[VTIME] = 10;
	term.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &term);
	while (1)
	{
		i = read(0, str, 100);
		write(1, str, i);
	}
	while (strcmp(str, "\n"))
		write(1, "\n", 1);
	return (0);
}
