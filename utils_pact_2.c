/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pact_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:33:17 by sgath             #+#    #+#             */
/*   Updated: 2021/03/27 18:17:02 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
** @params: char *str: строка, которую нужно продублировать
**			char **rem_str: строка, куда будет дублироваться
** TODO:dub_and_free: очищенная и записанная строка без ликов
*/
void
	dub_and_free(char **rem_str, char *str)
{
	if (*rem_str)
		free(*rem_str);
	*rem_str = ft_strdup(str);
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
	
	len = ft_strlen(name);
	while(envlst)
	{
		enviroment = envlst->content;
		if(!ft_strncmp(name, enviroment->value, len + 1))
			return(enviroment->argum);
		envlst = envlst->next;
	}
	return (NULL);
}