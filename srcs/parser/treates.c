/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:04:44 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/20 09:25:07 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char
	*treat_backslash(char **str, int quote, char *dir_addr)
{
	char	*left_token;
	char	*right_token;
	char	*token;

	(*str)++;
	if (!**str)
		return (ft_calloc(sizeof(char), 1));
	else if (quote == DQUOTE && !ft_strchr("$\\\"", **str))
		left_token = ft_substr((*str) - 1, 0, 2);
	else
		left_token = ft_substr(*str, 0, 1);
	(*str)++;
	if (quote)
	{
		(*str)--;
		right_token = treat_quotes(str, quote, dir_addr);
	}
	else if (**str)
		right_token = parse_token(str, dir_addr);
	else
		right_token = ft_calloc(sizeof(char), 1);
	token = ft_strjoin(left_token, right_token);
	free(left_token);
	free(right_token);
	return (token);
}

char
	*treat_tilda(char **str, char *dir_addr)
{
	char	*left_token;
	char	*right_token;
	char	*token;

	(*str)++;
	if (!(**str))
		return (ft_strdup(dir_addr));
	if ((**str) == '/')
		left_token = ft_strdup(dir_addr);
	else
		left_token = ft_strdup("~");
	if (**str)
		right_token = parse_token(str, dir_addr);
	else
		right_token = ft_calloc(sizeof(char), 1);
	token = ft_strjoin(left_token, right_token);
	free(left_token);
	free(right_token);
	return (token);
}

char
	*treat_quotes(char **str, int quote, char *dir_addr)
{
	size_t	len;
	char	*right_token;
	char	*token;
	char	*stop_symbols;

	(*str)++;
	stop_symbols = (quote == QUOTE) ? "'" : "\\\"";
	len = 0;
	while ((*str)[len] && !ft_strchr(stop_symbols, (*str)[len]))
		len++;
	token = ft_substr(*str, 0, len);
	*str += ((*str)[len] == quote) ? len + 1 : len;
	if (**str)
	{
		if (**str == BACKSLASH)
			right_token = treat_backslash(str, quote, dir_addr);
		else if (**str == QUOTE || **str == DQUOTE)
			right_token = treat_quotes(str, **str, dir_addr);
		else
			right_token = (**str) ? parse_token(str, dir_addr) :
				ft_calloc(sizeof(char), 1);
		token = ft_ownrealloc(&ft_strjoin, &token, right_token);
		free(right_token);
	}
	return (token);
}

char
	*treat_dollar(char **str, t_bool *is_quest)
{
	char	*token;
	int		len;

	*is_quest = FALSE;
	if (**str == '?' && (*is_quest = TRUE) && ((*str)++))
		return (ft_itoa(g_struct.error));
	len = 0;
	if (**str == '_' || ft_isalpha((*str)[0]))
		len++;
	if (!len && (ft_isdigit((*str)[0]) || ft_strchr(STRANGE_STR, (*str)[0])))
	{
		(*str)++;
		return (ft_strdup("$"));
	}
	if (!len && (*is_quest = TRUE))
		return (ft_strdup("$"));
	while (ft_isalnum((*str)[len]) || (*str)[len] == '_')
		len++;
	token = ft_substr(*str, 0, len);
	(*str) += len;
	return (token);
}
