/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 16:55:54 by sgath             #+#    #+#             */
/*   Updated: 2021/04/20 09:25:07 by ctragula         ###   ########.fr       */
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
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
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
	*validate_cmd(char *cmd, struct stat buff, char *path)
{
	int	h;

	h = 0;
	if (!ft_strchr(cmd, '/'))
	{
		(path) ? file_error(cmd, "command not found") :
		file_error(cmd, "No such file or directory");
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
	else if (buff.st_mode & S_IFDIR && (h = 126))
		file_error(cmd, "is a directory");
	g_struct.error = h;
	return ((h > 0) ? 0 : cmd);
}
