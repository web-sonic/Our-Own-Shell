/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:09:06 by sgath             #+#    #+#             */
/*   Updated: 2021/03/26 22:02:53 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void
	ft_unset(char **line, t_list *g_lstenv)
{
	t_env *enviroment;
	
	if(!line[0])
		return;
	while (g_lstenv->next)
	{
		enviroment = g_lstenv->content;
		g_lstenv = g_lstenv->next;
		if (!ft_strncmp(line[0], enviroment->value, ft_strlen(enviroment->value) + 1))
			free_g(g_lstenv);
	}
	
	
}