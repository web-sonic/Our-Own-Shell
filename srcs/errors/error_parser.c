/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:13:10 by sgath             #+#    #+#             */
/*   Updated: 2021/04/05 14:44:52 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list
	*error_parse(char *str, int c)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" `", 2);
	g_error = 258;
	if (c)
		ft_putchar_fd(c, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putendl_fd("'", 2);
	return (0);
}

void
	file_error(char *file, char *error)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(error, 2);
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
