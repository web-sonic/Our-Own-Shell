/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:11:41 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/07 16:35:24 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int
	add_fdin(t_cmd *cmd, char *token)
{
	if (cmd->is_fdin)
		close(cmd->fdin);
	if ((cmd->fdin = open(token, O_RDONLY, S_IRWXU)) < 0)
	{
		g_error = 1;
		file_error(token, strerror(errno));
		return (0);
	}
	cmd->is_fdin = TRUE;
	cmd->add_fd = -1;
	return (1);
}

int
	add_fdout(t_cmd *cmd, char *token)
{
	if (cmd->is_fdout)
		close(cmd->fdout);
	if (cmd->add_fd == 1)
	{
		cmd->fdout =
			open(token, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, S_IRWXU);
		if (cmd->fdout < 0)
		{
			g_error = errno;
			file_error(token, strerror(errno));
			return (0);
		}
		cmd->is_fdout = TRUE;
		cmd->add_fd = -1;
		return (1);
	}
	if ((cmd->fdout = open(token, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU)) < 0)
	{
		g_error = errno;
		file_error(token, strerror(errno));
		return (0);
	}
	cmd->is_fdout = TRUE;
	cmd->add_fd = -1;
	return (1);
}

int
	check_redirect(char *token, int *flag)
{
	if (*flag != -1)
	{
		error_parse(PARSE_ERROR, token[0]);
		free(token);
		return (1);
	}
	if (token[0] == LOW)
		*flag = 0;
	if (token[0] == GREAT && !token[1])
		*flag = 1;
	else if (token[0] == GREAT)
		*flag = 2;
	return (0);
}
