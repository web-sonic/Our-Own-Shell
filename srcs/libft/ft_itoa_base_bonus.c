/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 20:55:55 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/24 15:33:25 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(unsigned long num, size_t base)
{
	char	*numbers;
	char	*str;
	size_t	i;

	i = 0;
	numbers = "0123456789abcdef";
	if (base < 2 || base > 16 || (base != 10))
		return (0);
	i = ft_nbrlen(num, base);
	if (base != 10)
	{
		num *= -1;
		i--;
	}
	str = ft_calloc(ft_nbrlen(num, base) + 1, sizeof(char));
	while (num / base != 0)
	{
		str[--i] = numbers[(num % base)];
		num = num / base;
	}
	str[0] = numbers[num];
	return (str);
}
