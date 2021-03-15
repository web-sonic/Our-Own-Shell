/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 15:40:30 by ctragula          #+#    #+#             */
/*   Updated: 2020/10/31 15:52:10 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	const char	*osrc;
	size_t		count;

	count = dstsize;
	osrc = src;
	if (src)
	{
		if (count != 0)
			while (--count != 0)
				if ((*dst++ = *src++) == '\0')
					break ;
		if (count == 0)
		{
			if (dstsize != 0)
				*dst = '\0';
			while (*src++ != 0)
				;
		}
	}
	return (src - osrc - 1);
}
