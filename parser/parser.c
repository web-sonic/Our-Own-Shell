/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 17:08:42 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/19 18:20:32 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.c"

char
	*ft_strldup(char *str, size_t len)
{
	char	*dst;

	dst = ft_calloc(len, sizeof(char));
	ft_strlcpy(dst, str, len);
	return (dst);
}

char
	*ft_strownjoin(char *dst, char *src)
{
	char	*tmp_str;

	tmp_str = ft_strjoin(dst, src);
	free(dst);
	return (tmp_str);
}

void
	add_special(char **str, t_list *tokens)
{
	char	*token;

	token = ft_strldup(*str++, SYMBOL_LEN);
	ft_lstadd_back(&tokens, ft_lstnew(token));
}

void
	add_redirect(char **str, t_list *tokens)
{
	char	*token;

	if (**str + 1 == GREAT)
	{
		token = ft_strldup(*str, STR_REDIRECT_LEN);
		*str += 2;
	}
	else
		token = ft_strldup(*str++, SYMBOL_LEN);
	ft_lstadd_back(&tokens, ft_lstnew(token));
}

void
	add_argument(char **str, t_list *tokens)
{
	size_t	len;
	char	*token;

	len = 0;
	while (!ft_strchr(STOP_SYMBOLS, *str[len]))
		len++;
	token = ft_strldup(*str, len);
	*str += len;
	if (**str == QUOTE || **str == DQUOTE)
		token = ft_strownjoin(token, treat_quotes(str, tokens));
}

t_list
	*get_tokens(char *str)
{
	t_list	*tokens;

	while (*str != '\n')
	{
		ft_strtrim(str, SPACES);
		if (*str == PIPE || *str == SEMICOLON)
			add_special(&str, tokens);
		else if (*str == GREAT || *str == LOW)
			add_redirect(&str, tokens);
		else
			add_argument(&str, tokens);
	}
	return (tokens);
}