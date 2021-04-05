/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 13:11:33 by sgath             #+#    #+#             */
/*   Updated: 2021/04/05 14:51:36 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void
	line_split(t_env *arr_arg, char *line, int plus)
{
	int	i;

	i = 1;
	if (!ft_strchr(line, '='))
	{
		arr_arg->val = ft_strdup(line);
		arr_arg->arg = NULL;
		arr_arg->equally = 0;
	}
	else
	{
		plus == 0 ?
			(arr_arg->val = ft_substr(line, 0, super_strlen(0, '=', line))) :
			(arr_arg->val = ft_substr(line, 0, super_strlen(0, '+', line)));
		while (line[i] != '=')
			i++;
		arr_arg->arg = ft_substr(line, i + 1, super_strlen(i + 1, '\0', line));
		arr_arg->equally = 1;
	}
}

void
	free_env(void *env)
{
	t_env	*envt;

	envt = env;
	if (envt->arg)
	{
		free(envt->arg);
		envt->arg = 0;
	}
	free(envt->val);
	envt->val = 0;
	free(envt);
	envt = 0;
}

void
	*return_content(void *content)
{
	t_env	*old_env;
	t_env	*new_env;

	old_env = content;
	new_env = malloc(sizeof(t_env));
	new_env->arg = 0;
	if (old_env->arg)
		new_env->arg = ft_strdup(old_env->arg);
	new_env->val = ft_strdup(old_env->val);
	new_env->equally = old_env->equally;
	return (new_env);
}

char
	*ft_getenv(const char *name, t_list *envlst)
{
	int		len;
	t_env	*envt;

	len = ft_strlen(name);
	while (envlst)
	{
		envt = envlst->content;
		if (!ft_strncmp(name, envt->val, len + 1))
		{
			if (envt->arg)
				return (ft_strdup(envt->arg));
			else
				return (ft_calloc(sizeof(char), 1));
		}
		envlst = envlst->next;
	}
	return (ft_calloc(sizeof(char), 1));
}

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
		if (var->val)
		{
			tmp = ft_strjoin(var->val, "=");
			if (var->arg)
				env[i] = ft_strjoin(tmp, var->arg);
			else
				env[i] = ft_strdup(tmp);
			free(tmp);
			i++;
		}
		envlst = envlst->next;
	}
	return (env);
}
