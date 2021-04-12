/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 19:21:36 by sgath             #+#    #+#             */
/*   Updated: 2021/04/12 19:25:08 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd
	*cmd_clear(t_cmd *cmd)
{
	if (cmd->args)
		ft_wordtab_clear(cmd->args);
	close(cmd->fdin);
	close(cmd->fdout);
	cmd->fdin = 0;
	cmd->fdout = 0;
	cmd->is_fdin = FALSE;
	cmd->is_fdout = FALSE;
	free(cmd);
	return (0);
}
