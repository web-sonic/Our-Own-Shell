/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:16:56 by sgath             #+#    #+#             */
/*   Updated: 2021/04/05 15:52:02 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int
	check_flag_n(char *line)
{
	int flag;
	int i;

	i = 1;
	flag = 0;
	if (line[0] == '-' && line[1] == 'n')
	{
		flag = 1;
		while (line[++i] && flag == 1)
			if (line[i] != 'n')
				flag = 0;
	}
	return (flag);
}

int
	ft_echo(char **line)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (!line[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	while (line[i] && check_flag_n(line[i]) != 0)
	{
		n_flag = 1;
		i++;
	}
	while (line[i])
	{
		ft_putstr_fd(line[i], 1);
		if (line[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
