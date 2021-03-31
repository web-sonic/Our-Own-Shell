/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:16:56 by sgath             #+#    #+#             */
/*   Updated: 2021/03/31 12:22:03 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int
	count_arr(char **str)
{
	int	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

int
	ft_echo(char **line)
{
	int	count;
	int	i;
	int	n_flag;

	i = 1;
	count = count_arr(line);
	n_flag = 0;
	if (count != 1)
	{
		while (line[i] && !ft_strncmp(line[i], "-n", 3))
		{
			n_flag = 1;
			i++;
		}
		while (i < count)
		{
			ft_putstr_fd(line[i], 1);
			if (line[i++ + 1])
				ft_putstr_fd(" ", 1);
		}
	}
	if(n_flag == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
