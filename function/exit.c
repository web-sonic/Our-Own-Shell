/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:30 by sgath             #+#    #+#             */
/*   Updated: 2021/03/30 21:15:02 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

long long	super_atoi(const char *str)
{
	int			sign;
	long long	number;
	long long	checknum;

	number = 0;
	sign = 1;
	while ((*str >= 8 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		checknum = number;
		number = number * 10 + (*str - '0');
		str++;
		if (checknum > number && sign > 0)
			return (-1);
		else if (checknum > number)
			return (0);
	}
	number *= sign;
	return (number);
}

void
	ft_exit(char **line)
{
	int			i;
	long long	n;
	i = 0;
	n = 2;
	ft_putendl_fd("exit", 1);
	if (line[1] && line[2])
		ft_putendl_fd("bash: exit: too many arguments", 2);
	else if(!line[2] && line[1])
	{
		if (line[1][i] == '-')
			i++;
		while (line[1][i] && ft_isdigit(line[1][i]))
			i++;
		if (i == (int)ft_strlen(line[1]))
		{
			n = super_atoi(line[1]);
			if (i == ft_nbrlen(n, 10))
				exit(n);
		}
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(line[1], 1);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else
		n = 0;
	exit(n);
}
