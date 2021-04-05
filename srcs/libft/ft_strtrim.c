/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:49:32 by ctragula          #+#    #+#             */
/*   Updated: 2020/11/01 17:17:59 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;

	if (set && s1)
	{
		while (*s1 && ft_strchr(set, *s1))
			s1++;
		len = ft_strlen(s1);
		while (ft_strchr(set, *(s1 + len)))
			len--;
		if (*s1 == '\0')
			return (ft_strdup(s1));
		return (ft_substr(s1, 0, len + 1));
	}
	return (NULL);
}
