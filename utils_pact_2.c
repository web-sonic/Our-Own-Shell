/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pact_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:33:17 by sgath             #+#    #+#             */
/*   Updated: 2021/03/28 13:57:25 by ctragula         ###   ########.fr       */
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

char
	**ft_wordtab_realloc(char **wordtab, char *str)
{
	char	**tmp_tab;
	int		i;

	tmp_tab = wordtab;
	wordtab = malloc(sizeof(char *) * (ft_wordtab_count(tmp_tab) + 2));
	i = 0;
	while (tmp_tab[i])
	{
		wordtab[i] = ft_strdup(tmp_tab[i]);
		i++;
	}
	wordtab[i] = str;
	wordtab[i + 1] = 0;
	ft_wordtab_clear(tmp_tab);
	return (wordtab);
}