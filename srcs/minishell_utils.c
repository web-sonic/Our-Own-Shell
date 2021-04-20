/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:15:21 by sgath             #+#    #+#             */
/*   Updated: 2021/04/20 13:05:21 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int
	super_strlen(int start, char symbol, char *str)
{
	int	len;

	len = 0;
	while (str[start] != symbol && str[start++])
		len++;
	return (len);
}

char
	*mod_address(char *dir_add)
{
	char	*new_dir;
	char	*str;

	new_dir = ft_strdup(dir_add);
	str = ft_strrchr(new_dir, '/');
	if (str)
		*str = 0;
	return (new_dir);
}

void
	savefree(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void
	check_valid_shlvl(t_env **envt, int *shlvl)
{
	int	lvl;

	*shlvl = 1;
	if (!ft_digit((*envt)->arg))
	{
		lvl = ft_atoi((*envt)->arg);
		savefree((*envt)->arg);
		((*envt)->arg = 0);
		if (lvl < 999)
			(*envt)->arg = (lvl < 0) ? ft_strdup("0") : ft_itoa(lvl + 1);
		else if (lvl > 999)
		{
			ft_putstr_fd("bash: warning: shell level (", 1);
			ft_putnbr_fd(lvl, 1);
			ft_putendl_fd(") too high, resetting to 1", 1);
		}
	}
	else
		(*envt)->arg = ft_strdup("1");
}
