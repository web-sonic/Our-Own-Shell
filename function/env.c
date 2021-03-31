/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:45 by sgath             #+#    #+#             */
/*   Updated: 2021/03/31 12:21:33 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//t_list *envlst;

int
	ft_env(t_list **envlst)
{
	t_env	*enviroment;
	t_list	*tmp_lstenv;

	tmp_lstenv = *envlst;
	while(tmp_lstenv)
	{
		enviroment =tmp_lstenv->content;
		tmp_lstenv = tmp_lstenv->next;
		if (enviroment->equally == 1)
		{
			ft_putstr_fd(enviroment->value, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(enviroment->argum, 1);
		}
	}
	return (0);
}