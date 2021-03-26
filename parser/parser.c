/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemaritsu <kemaritsu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:52:46 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/26 17:21:07 by kemaritsu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void
	init_cmd(t_cmd *cmd, t_list *tokens)
{
	cmd->args = malloc(sizeof(char *));
	(cmd->args)[0] = ft_calloc(sizeof(char), 1);
	cmd->fderr = 0;
	cmd->fdin = 0;
	cmd->fdout = 0;
}

static char
	*parse_right_token(char **str)
{
	if (**str == QUOTE || DQUOTE)
		return (treat_quotes(str, **str));
	else if (**str == DOLLAR)
		return (treat_dollar(str));
	else if (**str == GREAT || **str == LOW)
		return (treat_redirect(str));
	else if (**str == '2' && (*str) + 1 == GREAT)
		return (treat_redirect(str));
	else if (**str == BACKSLASH)
		return (treat_backslash(str));
	else
		return (ft_calloc(sizeof(char), 1));
}

static char
	*parse_token(char **str)
{
	int		len;
	char	*left_token;
	char	*right_token;
	char	*token;
	t_list	*tokens;

	len = 0;
	while (!ft_strchr(STOP_SYMBOLS, (*str)[len]))
		len++;
	left_token = ft_strldup(*str, len + 1);
	*str += len;
	right_token = parse_right_token(str);
	token = ft_strjoin(left_token, right_token);
	free(left_token);
	free(right_token);
	return (token);
}

t_cmd
	parser(char *str, char **env)
{
	t_cmd	cmd;
	size_t  len;
	t_list	*tokens;
	char	*token;

	while (*str || *str != DIEZ)
	{
		token = parse_token(&str);
		ft_lstadd_back(&tokens, ft_lstnew(token));
	}
	init_cmd(&cmd, tokens);
	ft_lstclear(&tokens, &free);
	return (cmd);
}