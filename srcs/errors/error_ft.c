/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:55:54 by sgath             #+#    #+#             */
/*   Updated: 2021/04/06 14:12:34 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	valid_error(char *name, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(str, 1);
	ft_putendl_fd("': not a valid identifier", 1);
	return (1);
}

int
	empty_lst(char *name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (1);
}

char
	*validate_cmd(char *cmd)
{
	struct stat	buff;
	int			h;

	h = 0;
	if (!ft_strchr(cmd, '/'))
	{
		file_error(cmd, "command not found");
		h = NUM_COMMAND_NOT_FOUND;
	}
	else if (stat(cmd, &buff) < 0)
	{
		file_error(cmd, strerror(errno));
		h = NUM_COMMAND_NOT_FOUND;
	}
	else if (!(buff.st_mode & S_IXUSR))
	{
		file_error(cmd, "Permission denied");
		h = 126;
	}
	else if (buff.st_mode & S_IFDIR)
	{
		file_error(cmd, "is a directory");
		h = 126;
	}
	g_error = h;
	return ((h > 0) ? 0 : cmd);
}
