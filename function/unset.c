/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:09:06 by sgath             #+#    #+#             */
/*   Updated: 2021/03/30 16:48:55 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void
	free_env(void *env)
{
	t_env *enviroment;

	enviroment = env;
	if (enviroment->argum)
		free(enviroment->argum);
	free(enviroment->value);
	free(enviroment);
}

void
	ft_unset(char **line, t_list **envlst)
{
	t_env	*enviroment;
	t_list	*tmp_lstenv;
	t_list	*next_lstenv;
	int		i;

	if(!line[0])
		exit(0);
	enviroment = (*envlst)->content;
	if (!ft_strncmp(line[0], enviroment->value, ft_strlen(enviroment->value) + 1))
	{
		tmp_lstenv = (*envlst)->content;
		ft_lstdelone(envlst, &free_env);
		*envlst = tmp_lstenv;
		exit(0);
	}
	tmp_lstenv = *(envlst)->next;
	while (tmp_lstenv)
	{
		i = -1;
		enviroment = tmp_lstenv->content;
		while (line[++i])
		{
			if (!ft_strncmp(line[i], enviroment->value, ft_strlen(enviroment->value) + 1))
			{
				next_lstenv = tmp_lstenv->next;
				tmp_lstenv = next_lstenv->next;
				ft_lstdelone(tmp_lstenv->next, &free_env);
			}
		}
		tmp_lstenv = tmp_lstenv->next;
	}
	*envlst = tmp_lstenv;
}
