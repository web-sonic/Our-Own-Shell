/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:55:54 by sgath             #+#    #+#             */
/*   Updated: 2021/04/04 19:35:27 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int
	cd_error(char *dir_str, char *old_str)
{
	ft_putstr_fd("minishell: cd: ", 2);
	(!old_str) ? ft_putstr_fd(dir_str, 2) : ft_putstr_fd(old_str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

void
	exit_error(char *line)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(line, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int
	export_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 1);
	ft_putstr_fd(str, 1);
	ft_putendl_fd("': not a valid identifier", 1);
	return (1);
}

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

void
	print_errors(char *str)
{
	int	fd;

	if (ft_strncmp("./minishell", str, 12))
	{
		fd = open(str, O_RDONLY | O_DIRECTORY);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		if (strchr(str, '/'))
		{
			if (fd >= 0)
				ft_putendl_fd("is directory.", 2);
			else if (fd < 0)
				ft_putendl_fd(strerror(errno), 2);
			else
				ft_putendl_fd("permission denied", 2);
			close(fd);
			g_error = (fd < 0) ? 126 : NUM_COMMAND_NOT_FOUND;
			return ;
		}
		ft_putendl_fd("command not found", 2);
		g_error = NUM_COMMAND_NOT_FOUND;
	}
}
