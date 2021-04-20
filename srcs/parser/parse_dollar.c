/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:08:48 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/20 09:45:10 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char
	*goto_dollar(char **str, int *is_quote)
{
	char	*token;
	size_t	len;

	len = 0;
	while ((*str)[len] && ((*str)[len] != DOLLAR || *is_quote == 1))
	{
		if (((*str)[len] == QUOTE && *is_quote == 1) ||
			((*str)[len] == DQUOTE && *is_quote == 2))
			*is_quote = 0;
		else if ((*str)[len] == QUOTE && *is_quote == 0)
			*is_quote = 1;
		else if ((*str)[len] == DQUOTE && *is_quote == 0)
			*is_quote = 2;
		if ((*str)[len] == BACKSLASH && *is_quote != 1 && (*str)[len + 1])
			len += 2;
		else
			len++;
	}
	token = ft_substr(*str, 0, len);
	*str += len;
	return (token);
}

static void
	add_newarg_symbols(char *arg, char **new_arg)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = *new_arg;
	while (arg[i])
	{
		while (arg[i] && !ft_strchr("><", arg[i]))
			*tmp++ = arg[i++];
		if (arg[i])
		{
			*tmp++ = '"';
			*tmp++ = arg[i++];
			*tmp++ = '"';
		}
	}
}

static char
	*new_arg(char *arg)
{
	size_t	i;
	size_t	n;
	char	*new_arg;

	i = 0;
	n = 0;
	while (arg[i])
	{
		if (arg[i] == '>' || arg[i] == '<')
			n++;
		i++;
	}
	if (n)
	{
		new_arg = ft_calloc(ft_strlen(arg) + n * 2 + 1, sizeof(char));
		add_newarg_symbols(arg, &new_arg);
		free(arg);
		return (new_arg);
	}
	return (arg);
}

char
	*parse_vars(char *str, t_list *envlst, int *is_quote)
{
	char	*left_token;
	char	*right_token;
	char	*new_str;
	char	*dollar_arg;
	t_bool	is_quest;

	left_token = goto_dollar(&str, is_quote);
	if (*str == 0)
		return (left_token);
	if (*str)
		str++;
	dollar_arg = treat_dollar(&str, &is_quest);
	if (is_quest)
		right_token = ft_strdup(dollar_arg);
	else
		right_token = new_arg(ft_getenv(dollar_arg, envlst));
	left_token = ft_ownrealloc(&ft_strjoin, &left_token, right_token);
	free(dollar_arg);
	free(right_token);
	right_token = parse_vars(str, envlst, is_quote);
	new_str = ft_strjoin(left_token, right_token);
	free(left_token);
	free(right_token);
	return (new_str);
}
