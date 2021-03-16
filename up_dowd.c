/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_dowd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:45:42 by sgath             #+#    #+#             */
/*   Updated: 2021/03/16 17:18:50 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	main(int argc, char **argv, char const **envp)
{
	struct	termios term;
	char			*str;
	int				i;

	str = ft_calloc(sizeof(char), 2001);
	if (!str)
		return(0);
	tcgetattr(0, &term);
	//term.c_lflag &
	term.c_lflag &= ~(ECHO);
	//term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	i = read(0, str, i);
	write(1, str, i);
	write(1, "\n", 1);
	return (0);
}
