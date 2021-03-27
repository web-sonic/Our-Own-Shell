/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:52:46 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/27 17:00:13 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*g_lstenv;


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
	*treat_backslash(char **str, int quote)
{
	char	*left_token;
	char	*right_token;
	char	*token;

	(*str)++;
	if (!**str)
		return (ft_calloc(sizeof(char), 1));
	left_token = ft_strldup(*str, 2);
	(*str)++;
	if (quote)
		right_token = treat_quotes(str, quote);
	else if (**str)
		right_token = parse_token(str);
	else
		right_token = ft_calloc(sizeof(char), 1);
	token = ft_strjoin(left_token, right_token);
	free(left_token);
	free(right_token);
	return(token);
}

char
	*treat_dollar(char **str)
{
	char	*token;
	int		len;

	(*str)++;
	if (**str == '?')
	{
		(*str)++;
		return (ft_itoa(errno));
	}
	len = 0;
	while (!ft_strchr(STOP_SYMBOLS, (*str)[len]))
		len++;
	if (!len)
		token = ft_strdup("$");
	else
		token = ft_strldup(*str, len + 1);
	(*str) += len;
	return(token);
}

/*
** @params: char **str обрабатываемая строка
** 			int quote тип кавычек
** TODO: обрабатывает аргумент с кавычками в строке
** и сдивагет строку на следующую лексему
** @return char *token полученный аргумент
*/
char
	*treat_quotes(char **str, int quote)
{
	size_t	len;
	char	*left_token;
	char	*token;
	char	*stop_symbols;

	(*str)++;
	if (quote == QUOTE)
		stop_symbols = "'";
	else
		stop_symbols = "\\\"$";
	len = 0;
	while ((*str)[len] && !ft_strchr(stop_symbols, (*str)[len]))
		len++;
	left_token = ft_strldup(*str, len + 1);
	*str += len;
	if (**str == BACKSLASH)
		token = ft_strjoin(left_token, treat_backslash(str, quote));
	else if (**str == DOLLAR)
		token = ft_strjoin(left_token, treat_dollar(str));
	else if (*(*str)++)
		token = ft_strjoin(left_token, parse_token(str));
	else
		token = 0;
	free(left_token);
	return (token);
}


char
	*parse_token(char **str)
{
	size_t	len;
	char	*token;
	char	*left_token;

	len = 0;
	while ((*str)[len] && ft_strchr(STOP_SYMBOLS, (*str)[len]))
	{
		if ((*str)[len] == '2' && (*str)[len + 1] == GREAT)
			break;
		len++;
	}
	left_token = ft_strldup(*str, len + 1);
	*str += len;
	if (**str == QUOTE || **str == DQUOTE)
		token = ft_strjoin(left_token, treat_quotes(str, **str));
	else if (**str == BACKSLASH)
		token = ft_strjoin(left_token, treat_backslash(str, 0));
	else if (**str == DOLLAR)
		token = ft_strjoin(left_token, treat_dollar(str));
	else
		token = ft_strdup(left_token);
	free(left_token);
	return (token);
}

/*
** @params: char **str, t_list **tokens
** TODO: записывает в новую строку редирект
**	и сдивагет строку на следующую лексему
** @return char* : строка редирект
*/
static char
	*add_redirect(char **str)
{
	char	*token;

	if ((*str[2]) == GREAT && (*str)[0] == '2')
	{
		token = ft_strldup(*str, 4);
		*str += 3;
	}
	else if ((*str)[1] == GREAT)
	{
		token = ft_strldup(*str, 3);
		*str += 2;
	}
	else
		token = ft_strldup((*str)++, 2);
	return (token);
}

t_cmd
	parser(char *str)
{
	t_cmd	cmd;
	size_t  len;
	t_list	*tokens;
	char	*token;

	ft_getenv("USER");

	while (*str && *str != DIEZ)
	{
		if (*str == GREAT || *str == LOW)
			token = add_redirect(&str);
		else if (*str == GREAT && *(str + 1) == '2')
			token = add_redirect(&str);
		else
			token = parse_token(&str);
		if (*token)
			ft_lstadd_back(&tokens, ft_lstnew(token));
	}
	while (tokens)
	{
		token = tokens->content;
		ft_putendl_fd(token, 1);
		tokens = tokens->next;
	}
//	init_cmd(&cmd, tokens);
	ft_lstclear(&tokens, &free);
	return (cmd);
}