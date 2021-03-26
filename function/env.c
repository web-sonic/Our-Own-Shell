/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:45 by sgath             #+#    #+#             */
/*   Updated: 2021/03/26 21:43:40 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void
	ft_env(void)
// {
// 	int		i;
// 	t_list	*env_lst;

// 	i = -1;
// 	while (env[++i])
// 		ft_lstadd_back(&env_lst, ft_lstnew(env[i]));
	
// }
{
	t_env *enviroment;

	while(g_lstenv->next)
	{
		enviroment = g_lstenv->content;
		g_lstenv = g_lstenv->next;
	}
	enviroment = g_lstenv->content;
}