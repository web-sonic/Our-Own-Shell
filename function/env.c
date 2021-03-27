/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:45 by sgath             #+#    #+#             */
/*   Updated: 2021/03/27 16:02:14 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//t_list *g_lstenv;

void
	ft_env(void)
{
	t_env *enviroment;

	while(g_lstenv)
	{
		enviroment = g_lstenv->content;
		g_lstenv = g_lstenv->next;
		if (enviroment->argum)
		{
			ft_putstr_fd(enviroment->value, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(enviroment->argum, 1);
		}
	}
}