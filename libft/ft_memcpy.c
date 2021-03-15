/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:05:56 by ctragula          #+#    #+#             */
/*   Updated: 2020/11/02 19:34:02 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				inc;
	unsigned char		*str1;
	const unsigned char	*str2;

	str1 = dst;
	str2 = src;
	inc = 0;
	if (n != 0 && dst != src)
		while (inc++ < n)
			str1[inc - 1] = str2[inc - 1];
	return (dst);
}
