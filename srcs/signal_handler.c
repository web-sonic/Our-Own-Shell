/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:45:27 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/20 09:30:07 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	signal_handler(int key)
{
	int n;
	int	i;

	wait(&n);
	if (n == 2 || n == 3)
	{
		i = 0;
		while (i < g_struct.pid_count)
			kill(g_struct.pid[i++], n);
		if (key == 2)
		{
			ft_putchar_fd('\n', 1);
			g_struct.error = 130;
		}
		if (key == 3)
		{
			ft_putendl_fd("Quit: 3", 1);
			g_struct.error = 131;
		}
	}
}
