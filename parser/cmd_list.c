/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:08:42 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/24 12:33:37 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 
** @params: char *line строка
**			int quote тип кавычек
** TODO: считает длину строки в кавычках
** 		 учитывает экранирование
** @return длина строки
*/
static size_t
	skip_quotes(char *line, int quote)
{
	size_t	len;

	len = 1;
	while(line[len] && line[len] != quote)
	{
		if (line[len] == '\\' && line[len + 1] && quote != QUOTE)
			len++;
		len++;
	}
	if (!line[len])
		return (0);
	return (len);
}

/* 
** @params: t_list **cmd_lst указатель на список
** TODO: разбивает строку каждого элемента в списке на список
** 		 по пайпу.
** @return NULL
*/
static void
	get_pipes_lst(t_list **cmd_lst)
{
	t_list	*tmp_lst;
	char	*str;

	tmp_lst = *cmd_lst;
	while (tmp_lst)
	{
		str = tmp_lst->content;
		tmp_lst->content = split_cmdlst(str, PIPE);
		tmp_lst = tmp_lst->next;
	}
}

/* 
** @params: char *line строка
**			int stop_symbol символ, по которому делится строка
** TODO: разбивает строку на последовательность 
**		команд, редиректов, флагов и аргументов
** @return t_list *lst_cmd список команд
*/
t_list
	*split_cmdlst(char *line, int stop_symbol)
{
	t_list	*cmd_lst;
	char	*token;
	size_t	len;
	size_t	skip_len;
	char	*tmp_line;

	cmd_lst = 0;
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = 0;
	while (*line)
	{
		len = 0;
		line = ft_ownrealloc(&ft_strtrim, &line, " \t");
		while (line[len] && line[len] != stop_symbol)
		{
			if (line[len] == QUOTE || line[len] == DQUOTE)
				len += skip_quotes(line + len, line[len]) + 1;
			else if (line[len] == BACKSLASH && line[len + 1])
				len += 2;
			else
				len++;
		}
		token = ft_strldup(line, len + 1);
		tmp_line = ft_strdup(line + len + 1);
		free(line);
		line = tmp_line;
		ft_lstadd_back(&cmd_lst, ft_lstnew(token));
	}
	if (stop_symbol == SEMICOLON)
		get_pipes_lst(&cmd_lst);
	return (cmd_lst);
}

/* 
** @params: char *line
** TODO: разбивает строку на последовательность 
**		команд, редиректов, флагов и аргументов
** @return t_list *lst_cmd список команд
*/
t_list
	*get_cmds(char *line)
{
	t_list	*cmd_lst;

	cmd_lst = split_cmdlst(line, SEMICOLON);
	return (cmd_lst);
}