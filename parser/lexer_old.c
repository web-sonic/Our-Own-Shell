/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:04:04 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/23 12:11:56 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char
	*treat_backslash(char **str, int quote)
{
	char	*right_token;
	char	*left_token;
	char	*token;

	if (quote && ft_strchr("$\"\\", **str))
		left_token = ft_strldup(*str, 2);
	else
		left_token = ft_calloc(1, sizeof(char));
	(*str)++;
	if (!ft_strchr(SPACES, **str) || quote)
	{
		right_token = ft_strldup(*str, 2);
		(*str)++;
	}
	else
		right_token = ft_calloc(1, sizeof(char));
	if (quote)
		right_token = ft_strownjoin(right_token, treat_quotes(str, quote));
	else
		right_token = ft_strownjoin(right_token, treat_str(str));
	token = ft_strjoin(left_token, right_token);
	free(left_token);
	free(right_token);
	return(token);
}

char
	*treat_dollar(char **str)
{
	return("");
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
		token = ft_strjoin(left_token, treat_str(str));
	else
		token = 0;
	free(left_token);
	return (token);
}

char
	*treat_str(char **str)
{
	size_t	len;
	char	*token;
	char	*left_token;

	len = 0;
	while ((*str)[len] && !ft_strchr(STOP_SYMBOLS, (*str)[len]))
		len++;
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
** TODO: добавляет в список новую лексему спец. символ
**	и сдивагет строку на следующую лексему
** @return NULL
*/
static void
	add_special(char **str, t_list **tokens)
{
	char	*token;

	token = ft_strldup((*str)++, 2);
	ft_lstadd_back(tokens, ft_lstnew(token));
}

/*
** @params: char **str, t_list **tokens
** TODO: добавляет в список новую лексему редирект
**	и сдивагет строку на следующую лексему
** @return NULL
*/
static void
	add_redirect(char **str, t_list **tokens)
{
	char	*token;

	if ((*str)[1] == GREAT)
	{
		token = ft_strldup(*str, 3);
		*str += 2;
	}
	else
		token = ft_strldup((*str)++, 2);
	ft_lstadd_back(tokens, ft_lstnew(token));
}

/* 
** @params: char *str, t_list **tokens
** TODO: добавляет в список новую лексему аргумент
**	и сдивагет строку на следующую лексему
** @return NULL
*/
static void
	add_argument(char **str, t_list **tokens)
{
	char *token;

	token = treat_str(str);
	if (token && *token)
		ft_lstadd_back(tokens, ft_lstnew(token));
}

/* 
** @params: char *str
** TODO: разбивает строку на лексемы/ токены
** @return t_list *tokens список токенов
*/
t_list
	*lexer(char *str)
{
	t_list	*tokens;

	tokens = NULL;
	while (*str)
	{
		str = ft_strtrim(str, SPACES);
		if (*str == PIPE || *str == SEMICOLON)
			add_special(&str, &tokens);
		else if (*str == GREAT || *str == LOW)
			add_redirect(&str, &tokens);
		else if (*str)
			add_argument(&str, &tokens);
	}
	return (tokens);
}