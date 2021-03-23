/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 17:16:56 by sgath             #+#    #+#             */
/*   Updated: 2021/03/23 17:55:36 by sgath            ###   ########.fr       */
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
	char *new_name;

	i = -1;
	count = count_arr(line);
	
	if (ft_strncmp(line[0], "-n"))
	{
		while(++(i+1) < count)
			ft_strjoin(new_name, " ", )
	}
	while (++i < count && line[i][0] != '#')
	{
		ft_putstr_fd(line[i], 1);
		if (line[i + 1])
			ft_putstr_fd(" ", 1);
	}
	ft_putstr_fd("\n", 1);
}