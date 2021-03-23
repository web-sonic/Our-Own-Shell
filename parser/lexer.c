/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:08:14 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/23 13:21:38 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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