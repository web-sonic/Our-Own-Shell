/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 05:27:16 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/04 05:27:59 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void
	exceptions(char c)
{
	if (c == '.')
	{
		g_error = 2;
		ft_putendl_fd("minishell: .: filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
	}
	else
	{
		g_error = 126;
		ft_putendl_fd("minishell: /Users: is a directory", 2);
	}
}