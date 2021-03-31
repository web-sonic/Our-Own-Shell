/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getallenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 18:44:33 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/31 11:59:17 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	**getallenv(t_list *envlst)
{
	char	**env;
	t_env	*var;
	char	*tmp;
	int		i;

	i = 0;
	env = ft_calloc(sizeof(char *), ft_lstsize(envlst) + 1);
	while (envlst)
	{
		var = envlst->content;
		tmp = ft_strjoin(var->value, "=");
		env[i] = ft_strjoin(tmp, var->argum);
		free(tmp);
		i++;
		envlst = envlst->next;
	}
	return (env);
}