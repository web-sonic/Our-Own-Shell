/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 05:22:25 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/04 05:22:34 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*ft_strtolower(char *str)
{
	size_t	i;
	char	*new_str;

	new_str = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	i = 0;
	while (str[i])
	{
		new_str[i] = ft_tolower(str[i]);
		i++;
	}
	return (new_str);
}