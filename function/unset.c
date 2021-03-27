/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:09:06 by sgath             #+#    #+#             */
/*   Updated: 2021/03/27 16:43:02 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void
	free_lst(t_list	**tmp_lstenv)
{
	t_env	*enviroment;

	enviroment = (*tmp_lstenv)->content;
	free(enviroment->argum);
	free(enviroment->value);
	free((*tmp_lstenv)->content);
	//ft_lstdelone(tmp_lstenv, free); ?????
}

void
	ft_unset(char **line)
{
	t_env	*enviroment;
	t_list	*tmp_lstenv;
	int		i;

	tmp_lstenv = g_lstenv;
	i = -1;
	if(!line[0])
		return;
	while (tmp_lstenv)
	{
		enviroment = tmp_lstenv->content;
		tmp_lstenv = tmp_lstenv->next;
		while (line[++i])
			if (!ft_strncmp(line[0], enviroment->value, ft_strlen(enviroment->value) + 1))
				free_lst(&g_lstenv);
	}
}

// int main () 
// {
//    printf("PATH : %s\n", getenv("PATH"));
//    printf("HOME : %s\n", getenv("HOME"));
//    printf("ROOT : %s\n", getenv("RO"));

//    return(0);
// }