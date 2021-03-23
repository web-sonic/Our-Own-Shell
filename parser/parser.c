/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:08:42 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/21 13:57:43 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 
** @params: char *line
** TODO: разбивает строку на последовательность 
**		команд, редиректов, флагов и аргументов
** @return t_list *lst_cmd список команд
*/
t_list
	*ft_parser(char *line)
{
	t_list	*lst_cmd;
	char	*token;

	lst_cmd = NULL;
	line[ft_strlen(line) -1] = '\0';
	lst_cmd = lexer(line);
	while (lst_cmd)
	{
		token = lst_cmd->content;
		ft_putendl_fd(token, 1);
		lst_cmd = lst_cmd->next;
	}
	return (lst_cmd);
}