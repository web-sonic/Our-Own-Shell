/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:08:42 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/19 11:25:48 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.c"

/* 
** @params: char *str обрабатываемая строка
**			char *name: название minishell
** TODO разбивает строку на список структур, которые содержат команду,
**		 ее аргументы, информацию о дескрипторах входных и выходных данных
** @return: t_list commands
*/
t_list	*parser(char *str)
{
	t_list	*processes;

	add_process(NULL, processes);
	while (*str)
	{
		ft_strtrim(str, " \t");
		if (*str == '"' || *str == '\'')
			if (!add_with_quotes(&str, processes))
				return (NULL);
		else if (*str == '>' || *str == '<')
			if (!add_redirect(&str, processes))
				return (NULL);
		else if (*str == '|')
			if (!add_command(&str, processes))
				return (NULL);
		else if (*str == ';')
			if (!add_process(&str, processes))
				return (NULL);
		else
			if (!add_argument(&str, processes))
				return (NULL);
	}
	return (processes);
}