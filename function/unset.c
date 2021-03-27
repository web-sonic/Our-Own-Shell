/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:09:06 by sgath             #+#    #+#             */
/*   Updated: 2021/03/27 17:36:36 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void
	free_env(t_env *enviroment)
{
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
	int		i;

	if(!line[0])
		return;
	enviroment = (*envlst)->content;
	if (!ft_strncmp(line[0], enviroment->value, ft_strlen(enviroment->value) + 1))
	{
		tmp_lstenv = (*envlst)->next;
		ft_lstdelone(envlst, &free_env);
		envlst = tmp_lstenv;
		return;
	}
	tmp_lstenv = envlst;
	while (tmp_lstenv)
	{
		i = -1;
		enviroment = tmp_lstenv->next;
		while (line[++i])
		{
			if (!ft_strncmp(line[i], enviroment->value, ft_strlen(enviroment->value) + 1))
			{
				tmp_lstenv->next->next;
				ft_lstdelone(&tmp_lstenv->next, &free_env);
				envlst = tmp_lstenv;
			}
		}
		tmp_lstenv = tmp_lstenv->next;
	}
}

// int main () 
// {
//    printf("PATH : %s\n", getenv("PATH"));
//    printf("HOME : %s\n", getenv("HOME"));
//    printf("ROOT : %s\n", getenv("RO"));

//    return(0);
// }