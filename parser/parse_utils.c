/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 07:03:30 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/03 17:13:05 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t
	skip_quotes(char *str, int quote)
{
	size_t	len;

	len = 1;
	while (str[len] && str[len] != quote)
	{
		if (str[len] == '\\' && str[len + 1] && quote != QUOTE)
			len++;
		len++;
	}
	if (!str[len])
		return (0);
	return (len);
}

void
	skip_spaces(char **str, char *spaces)
{
	size_t	len;

	len = 0;
	while ((*str)[len] && ft_strchr(spaces, (*str)[len]))
		len++;
	(*str) += len;
}

char
	*goto_stopsymbol(char **str, char stop_symbol)
{
	size_t	len;
	char	*token;
	size_t	skip_len;

	len = 0;
	while ((*str)[len] && (*str)[len] != stop_symbol)
	{
		if ((*str)[len] == DQUOTE || (*str)[len] == QUOTE)
		{
			if (!(skip_len = skip_quotes(*str + len, (*str)[len])))
				return (0);
			len += skip_len + 1;
		}
		else if ((*str)[len] == BACKSLASH && (*str)[len + 1])
			len += 2;
		else
			len++;
	}
	token = ft_substr(*str, 0, len);
	*str += ((*str)[len]) ? len + 1 : len;
	return (token);
}
