/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:30 by sgath             #+#    #+#             */
/*   Updated: 2021/04/04 13:51:52 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long
	super_atoi(const char *str)
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

static int
	check_argum_exit(char *line)
{
	int			i;
	long long	n;

	i = 0;
	if (line[i] == '-' || line[i] == '+')
		i++;
	while (line[i] && ft_isdigit(line[i]))
		i++;
	if (i == (int)ft_strlen(line))
	{
		n = super_atoi(line);
		if (line[0] == '+')
			i--;
		if (i == ft_nbrlen(n, 10))
			exit(n);
	}
	exit_error(line);
	exit(255);
}

int
	ft_exit(char **line)
{
	int			i;
	long long	n;

	i = 0;
	n = 0;
	ft_putendl_fd("exit", 1);
	if (line[1] && line[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		exit(1);
	}
	else if (!line[2] && line[1])
		check_argum_exit(line[1]);
	exit(n);
}
