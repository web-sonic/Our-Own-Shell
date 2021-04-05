/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:35:04 by ctragula          #+#    #+#             */
/*   Updated: 2021/01/16 17:57:49 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lennum(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*s;
	int		len;
	int		sign;

	sign = 1;
	if (n < 0)
		sign *= -1;
	len = ft_lennum(n);
	if (!(s = ft_calloc(len + 1, sizeof(char))))
		return (NULL);
	if (n < 0)
		s[0] = '-';
	s[len] = '\0';
	while (n >= 10 || n <= -10)
	{
		s[--len] = ((n % 10) * sign + '0');
		n /= 10;
	}
	s[--len] = n * sign + '0';
	return (s);
}
