/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:30:45 by ctragula          #+#    #+#             */
/*   Updated: 2020/11/06 11:04:09 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start || ft_strlen(s) == 0)
	{
		if (!(subs = ft_calloc(1, sizeof(char))))
			return (NULL);
	}
	else if (ft_strlen(s) < start + len)
	{
		if (!(subs = ft_calloc(ft_strlen(s) - start + 1, sizeof(char))))
			return (NULL);
		ft_strlcpy(subs, s + start, start - len);
	}
	else
	{
		if (!(subs = ft_calloc(len + 1, sizeof(char))))
			return (NULL);
		ft_strlcpy(subs, s + start, len + 1);
	}
	return (subs);
}
