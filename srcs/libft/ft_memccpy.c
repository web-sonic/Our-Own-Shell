/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:00:51 by ctragula          #+#    #+#             */
/*   Updated: 2020/11/02 19:32:49 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				inc;
	unsigned char		*str1;
	const unsigned char	*str2;

	str1 = (unsigned char *)dst;
	str2 = (unsigned char *)src;
	inc = 0;
	while ((inc++ < n) && (*str2 != (unsigned char)c))
		*str1++ = *str2++;
	if (*str2 == (unsigned char)c && inc <= n)
	{
		*str1++ = *str2;
		return (str1);
	}
	return (NULL);
}
