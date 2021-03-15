/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:34:14 by ctragula          #+#    #+#             */
/*   Updated: 2020/10/30 18:37:53 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*odst;
	unsigned char	*osrc;

	odst = (unsigned char *)dst;
	osrc = (unsigned char *)src;
	if (odst < osrc)
		while (len--)
			*odst++ = *osrc++;
	else if (odst > osrc)
	{
		odst += len;
		osrc += len;
		while (len--)
			*--odst = *--osrc;
	}
	return (dst);
}
