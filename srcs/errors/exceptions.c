/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 05:27:16 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/20 09:25:07 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void
	exceptions(char *c)
{
	if (c[0] == '.')
	{
		g_struct.error = 2;
		ft_putendl_fd("minishell: .: filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
	}
	else
	{
		g_struct.error = 126;
		!c[1] ? ft_putendl_fd("minishell: /: is a directory", 2) :
		ft_putendl_fd("minishell: /Users: is a directory", 2);
	}
}
