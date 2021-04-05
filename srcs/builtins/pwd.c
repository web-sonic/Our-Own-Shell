/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:09:02 by sgath             #+#    #+#             */
/*   Updated: 2021/04/05 12:47:34 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int
	ft_pwd(char **line)
{
	char	*dir;

	dir = ft_calloc(sizeof(char), PATH_MAX);
	if (!dir)
		return (1);
	if (!getcwd(dir, PATH_MAX - 1))
		return (1);
	if (line[1])
	{
		if (line[1][0] == '-' && line[1][1] != '\0' && line[1][1] != '-')
			return (flag_error(line[0], line[1]));
	}
	ft_putendl_fd(dir, 1);
	free(dir);
	return (0);
}
