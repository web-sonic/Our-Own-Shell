/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:08:48 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/05 12:44:30 by sgath            ###   ########.fr       */
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
		right_token = ft_getenv(dollar_arg, envlst);
	left_token = ft_ownrealloc(&ft_strjoin, &left_token, right_token);
	free(dollar_arg);
	free(right_token);
	right_token = parse_vars(str, envlst, is_quote);
	new_str = ft_strjoin(left_token, right_token);
	free(left_token);
	free(right_token);
	return (new_str);
}
