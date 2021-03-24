/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:16:56 by sgath             #+#    #+#             */
/*   Updated: 2021/03/24 20:17:34 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int
	count_arr(char **str)
{
	int	count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

void
	ft_echo(char **line)
{
	int	count;
	int	i;
	int	n_flag;

	i = -1;
	count = count_arr(line);
	n_flag = 0;
	if (count != 0)
	{
		while (!ft_strncmp(line[0], "-n", 3))
		{
			n_flag = 1;
			++i;
		}
		while (++i < count && line[i][0] != '#') //??
		{
			ft_putstr_fd(line[i], 1);
			if (line[i + 1])
				ft_putstr_fd(" ", 1);
		}
	}
	if(n_flag == 0)
		ft_putstr_fd("\n", 1);
}
