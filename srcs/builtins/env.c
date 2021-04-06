/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:45 by sgath             #+#    #+#             */
/*   Updated: 2021/04/06 15:30:16 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int
	ft_env(t_list *envlst)
{
	t_env	*envt;
	t_list	*tmp_lstenv;

	tmp_lstenv = envlst;
	while (tmp_lstenv)
	{
		envt = tmp_lstenv->content;
		if (envt->val)
		{
			tmp_lstenv = tmp_lstenv->next;
			if (envt->equally == 1)
			{
				ft_putstr_fd(envt->val, 1);
				ft_putchar_fd('=', 1);
				ft_putendl_fd(envt->arg, 1);
			}
		}
	}
	return (0);
}
