/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:55:54 by sgath             #+#    #+#             */
/*   Updated: 2021/04/04 06:03:31 by ctragula         ###   ########.fr       */
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
	ft_putstr_fd(line, 1);
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
	if (arg[1])
		ft_putchar_fd(arg[1], 2);
	ft_putendl_fd(": invalid option", 2);
	if (!ft_strncmp(name, "export", 7))
	{
		ft_putendl_fd("export: usage: export [-nf] [name[=value] ...] or export -p)", 2);
		return (2);
	}
	else if (!ft_strncmp(name, "cd", 3))
		ft_putendl_fd("cd: usage: cd [-L|-P] [dir]", 2);
	else if (!ft_strncmp(name, "env", 4))
	{
		ft_putstr_fd("usage: env [-iv] [-P utilpath] [-S string] [-u name]", 2);
		ft_putendl_fd("           [name=value ...] [utility [argument ...]]", 2);
	}
	else if (!ft_strncmp(name, "pwd", 4))
		ft_putendl_fd("pwd: usage: pwd [-LP]", 2);
	else if (!ft_strncmp(name, "unset", 6))
	{
		ft_putendl_fd("unset: usage: unset [-f] [-v] [name ...]", 2);
		return (2);
	}
	return (1);
}

void
	print_errors(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (strchr(str, '/'))
	{
		if (open(str, O_RDONLY | O_DIRECTORY) >= 0)
		{
			ft_putendl_fd("is directory.", 2);
			g_error = 126;
		}
		else if (open(str, O_RDWR) < 0)
		{
			ft_putendl_fd(strerror(errno), 2);
			g_error = NUM_COMMAND_NOT_FOUND;
		}
		else
		{
			ft_putendl_fd("permission denied", 2);
			g_error = 126;
		}
		return ;
	}
	ft_putendl_fd("command not found", 2);
	g_error = NUM_COMMAND_NOT_FOUND;
}
