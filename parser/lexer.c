/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 18:04:04 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/20 11:47:59 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
** @params: char **str
** TODO: обрабатывает аргумент с кавычками в строке
** и сдивагет строку на следующую лексему
** @return char *token полученный аргумент
*/
char
	*treat_quotes(char **str)
{
	char	quote;
	size_t	len;
	char	*left_token;
	char	*right_token;
	char	*token;

	quote = *(*str)++;
	len = 0;
	while ((*str)[len] != quote && (*str[len - 1]) != BACKSLASH)
		len++;
	left_token = ft_strldup(*str, len);
	*str += len;
	//treat_shield(&left_token, quote);
	len = 0;
	while (!ft_strchr(STOP_SYMBOLS, (*str)[len]))
		len++;
	right_token = ft_strldup(*str, len + 1);
	*str += len + 1;
	token = ft_strjoin(left_token, right_token);
	free(left_token);
	free(right_token);
	if (**str == QUOTE || **str == DQUOTE)
		token = ft_strownjoin(token, treat_quotes(str));
	return (token);
}

char
	*treat_backslash(char **str, char quote)
{
	size_t	len;
	char	*left_token;
	char	*right_token;
	char	*token;

	quote 

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
	size_t	len;
	char	*token;

	len = 0;
	while (!ft_strchr(STOP_SYMBOLS, (*str)[len]))
		len++;
	token = ft_strldup(*str, len + 1);
	*str += len;
	if (**str == QUOTE || **str == DQUOTE)
		token = ft_strownjoin(token, treat_quotes(str));
	if (**str == BACKSLASH)
		token = ft_strownjoin(token, treat_backslash(str));
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