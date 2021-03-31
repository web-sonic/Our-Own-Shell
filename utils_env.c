/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:11:33 by sgath             #+#    #+#             */
/*   Updated: 2021/03/31 13:18:59 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	line_split(t_env *arr_arg, char *line)
{
	int i;

	i = 1;
	if(!ft_strchr(line, '='))
	{
		arr_arg->value = ft_strdup(line);
		arr_arg->argum = NULL;
		arr_arg->equally = 0;
	}
	else
	{
		arr_arg->value = ft_substr(line, 0, super_strlen(0, '=', line));
		while (line[i] != '=')
			i++;
		arr_arg->argum = ft_substr(line, i + 1, super_strlen(i + 1, '\0', line));
		arr_arg->equally = 1;
	}
}

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
	*return_content(void *content)
{
	return (content);
}

char
	*ft_getenv(const char *name, t_list	*envlst)
{
	int		len;
	t_env	*enviroment;
	char	*str;

	str = 0;
	len = ft_strlen(name);
	while(envlst)
	{
		enviroment = envlst->content;
		if(!ft_strncmp(name, enviroment->value, len + 1))
			return (ft_strdup(enviroment->argum));
		envlst = envlst->next;
	}
	return (ft_calloc(sizeof(char), 1));
}
