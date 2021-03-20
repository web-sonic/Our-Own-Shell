/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:48:26 by sgath             #+#    #+#             */
/*   Updated: 2021/03/19 18:09:46 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	check_signal(char **rem_str, char *str)
{
	if(!ft_strncmp(str, "\4", 2) && !(*rem_str))
	{
		ft_putstr_fd("\n./minishell> exit\n", 1);
		exit(0);
	}
	else if (!ft_strncmp(str, "\3", 2))
	{
		ft_putstr_fd("\n./minishell> ", 1);
	}
}