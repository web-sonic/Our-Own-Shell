/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:09:06 by sgath             #+#    #+#             */
/*   Updated: 2021/03/31 14:28:15 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void
	ft_unset(char **line, t_list **envlst)
{
	t_env	*enviroment;
	t_list	*tmp_lstenv;
	t_list	*next_lstenv;
	int		i;

	if(!line[1])
		return ;
	enviroment = (*envlst)->content;
	i = 0;
	tmp_lstenv = *envlst;
	while (line[++i])
	{
		if (!ft_strncmp(line[i], enviroment->value, ft_strlen(enviroment->value) + 1))
		{
			tmp_lstenv->next = (*envlst)->next;
			ft_lstdelone((*envlst), &free_env);
			*envlst = tmp_lstenv;
		}
	}
	next_lstenv = (*envlst)->next;
	while (next_lstenv)
	{
		i = 0;
		enviroment = next_lstenv->content;
		while (line[++i])
		{
			if (!ft_strncmp(line[i], enviroment->value, ft_strlen(enviroment->value) + 1))
			{
				tmp_lstenv->next = next_lstenv->next;
				ft_lstdelone(next_lstenv, &free_env);
				next_lstenv = tmp_lstenv->next;
				
			}
		}
		tmp_lstenv = tmp_lstenv->next;
		next_lstenv = next_lstenv->next;
	}
}
