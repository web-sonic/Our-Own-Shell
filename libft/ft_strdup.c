/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 17:40:30 by ctragula          #+#    #+#             */
/*   Updated: 2020/11/08 11:15:49 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	count;
	char	*dest;

	count = ft_strlen(s1);
	if (!(dest = ft_calloc(count + 1, sizeof(char))))
		return (NULL);
	ft_strlcpy(dest, s1, count + 1);
	return (dest);
}
