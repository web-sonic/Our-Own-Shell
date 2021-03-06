/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 12:48:48 by sgath             #+#    #+#             */
/*   Updated: 2021/04/15 19:12:01 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int
	ft_digit(char *str)
{
	int digit;
	int i;

	i = 0;
	digit = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && digit == 0)
	{
		if (!ft_isdigit(str[i]))
			digit = 1;
		i++;
	}
	return (digit);
}
