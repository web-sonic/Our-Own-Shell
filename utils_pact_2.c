/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pact_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:33:17 by sgath             #+#    #+#             */
/*   Updated: 2021/03/28 19:02:34 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
** @params: char *str: строка, которую нужно продублировать
**			char **rem_str: строка, куда будет дублироваться
** TODO:dub_and_free: очищенная и записанная строка без ликов
*/
int
	dub_and_free(char **rem_str, char *str)
{
	if (*rem_str)
		free(*rem_str);
	*rem_str = ft_strdup(str);
	return (1);
}

/* 
** @params: char *str: строка, которая принимает символы, введеные с консоли
**			char **rem_str: строка, хранящаяя символы введеные с консоли
** TODO: write_new_symbol_str: Посимвольно добавляет к rem_str введенные в консоль символы
*/
void
	write_new_symbol_str(char **rem_str, char *str)
{
	char *tmp;
	int i = -1;

	while (str[++i])
	{
		if(!ft_isprint(str[i]) && str[i] != '\n')
			return;
	}
	if (!(*rem_str))
		*rem_str = ft_strdup(str);
	else
	{
		tmp = ft_strjoin(*rem_str, str);
		free(*rem_str);
		*rem_str = tmp;
	}
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

int
	cmp_sort(t_env *cont, t_env *next)
{
	return(ft_strncmp(cont->value, next->value, ft_strlen(cont->value) + 1));
}

void
	line_split(t_env *arr_arg, char *line)
{
	int i;

	i = 1;
	if(!ft_strchr(line, '='))
	{
		arr_arg->value = ft_strdup(line);
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