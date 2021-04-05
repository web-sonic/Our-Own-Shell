/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 11:45:27 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/05 12:48:40 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	signal_handler(int key)
{
	if (key == 2)
	{
		ft_putchar_fd('\n', 1);
		g_error = 130;
	}
	if (key == 3)
	{
		ft_putendl_fd("Quit: 3", 1);
		g_error = 131;
	}
}
