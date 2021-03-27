/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:09:06 by sgath             #+#    #+#             */
/*   Updated: 2021/03/27 15:55:00 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void
	free_lst(void)
{
	t_env	*enviroment;

	enviroment = g_lstenv->content;
	free(enviroment->argum);
	free(enviroment->value);
	ft_lstdelone(g_lstenv, free);
}

void
	ft_unset(char **line)
{
	t_env	*enviroment;
	int		i;
	
	i = -1;
	if(!line[0])
		return;
	
	while (g_lstenv)
	{
		enviroment = g_lstenv->content;
		g_lstenv = g_lstenv->next;
		while (line[++i])
			if (!ft_strncmp(line[0], enviroment->value, ft_strlen(enviroment->value) + 1))
				free_lst();
	}
}

// int main () 
// {
//    printf("PATH : %s\n", getenv("PATH"));
//    printf("HOME : %s\n", getenv("HOME"));
//    printf("ROOT : %s\n", getenv("RO"));

//    return(0);
// }