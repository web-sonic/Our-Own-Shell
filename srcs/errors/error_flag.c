/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:00:40 by sgath             #+#    #+#             */
/*   Updated: 2021/04/20 09:34:23 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int
	flag_error(char *name, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": -", 2);
	ft_putchar_fd(arg[1], 2);
	ft_putendl_fd(": invalid option", 2);
	if (!ft_strncmp(name, "export", 7))
	{
		ft_putstr_fd(name, 2);
		ft_putendl_fd(FLAG_ERROR_EXP, 2);
		return (2);
	}
	(!ft_strncmp(name, "cd", 3)) ? ft_putendl_fd(FLAG_ERROR_CD, 2) : 0;
	if (!ft_strncmp(name, "env", 4))
	{
		ft_putstr_fd(FLAG_ERROR_ENV1, 2);
		ft_putendl_fd(FLAG_ERROR_ENV2, 2);
	}
	if (!ft_strncmp(name, "pwd", 4))
		ft_putendl_fd(FLAG_ERROR_PWD, 2);
	if (!ft_strncmp(name, "unset", 6))
	{
		ft_putendl_fd(FLAG_ERROR_UNSET, 2);
		return (2);
	}
	return (1);
}
