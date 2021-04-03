/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:08:42 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/03 17:13:39 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void
	get_pipes_lst(t_list *cmd_lst, t_list **magic_lst)
{
	char	*magic;

	while (cmd_lst)
	{
		magic = cmd_lst->content;
		cmd_lst->content = split_cmdlst(magic, PIPE, NULL);
		cmd_lst = cmd_lst->next;
		ft_lstadd_back(magic_lst, ft_lstnew(magic));
	}
}

t_list
	*split_cmdlst(char *line, int stop_symbol, t_list **magic_lst)
{
	t_list	*cmd_lst;
	char	*token;

	cmd_lst = 0;
	while (*line)
	{
		skip_spaces(&line, SPACES);
		if (*line == stop_symbol)
		{
			ft_lstclear(&cmd_lst, &free);
			return (error_parse(PARSE_ERROR, stop_symbol));
		}
		token = goto_stopsymbol(&line, stop_symbol);
		if (!token)
			return (error_parse(PARSE_ERROR, 0));
		if (!(*token) && *line)
			return (error_parse(PARSE_ERROR, stop_symbol));
		ft_lstadd_back(&cmd_lst, ft_lstnew(token));
	}
	if (stop_symbol == SEMICOLON)
		get_pipes_lst(cmd_lst, magic_lst);
	return (cmd_lst);
}

t_list
	*get_cmds(char *line, t_list **magic_lst)
{
	t_list	*cmd_lst;

	cmd_lst = split_cmdlst(line, SEMICOLON, magic_lst);
	return (cmd_lst);
}
