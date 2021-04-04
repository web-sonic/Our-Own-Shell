/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ownrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:37:36 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/04 06:38:03 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char
	*ft_ownrealloc(char *(*f)(const char *, const char *), char **s1, char *s2)
{
	char	*tmp_str;

	tmp_str = f(*s1, s2);
	free(*s1);
	return (tmp_str);
}
