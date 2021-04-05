/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:38:04 by ctragula          #+#    #+#             */
/*   Updated: 2020/10/31 13:07:55 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*odst;
	const char	*osrc;
	size_t		count;
	size_t		dstlen;

	odst = dst;
	osrc = src;
	count = dstsize;
	while (count-- != 0 && *dst != '\0')
		dst++;
	dstlen = dst - odst;
	count = dstsize - dstlen;
	if (count-- == 0)
		return (dstlen + ft_strlen(src));
	while (*src != '\0')
	{
		if (count != 0)
		{
			*dst++ = *src;
			count--;
		}
		src++;
	}
	*dst = '\0';
	return (dstlen + (src - osrc));
}
