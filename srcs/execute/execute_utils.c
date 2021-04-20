/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 19:21:36 by sgath             #+#    #+#             */
/*   Updated: 2021/04/20 08:36:42 by ctragula         ###   ########.fr       */
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

t_list
	*parse_pipes(t_list *pipe_lst, t_list *envlst,
	char *dir_add)
{
	t_list	*cmd_lst;
	t_cmd	*cmd;

	cmd_lst = 0;
	while (pipe_lst)
	{
		cmd = parser(pipe_lst->content, envlst, dir_add);
		pipe_lst = pipe_lst->next;
		ft_lstadd_back(&cmd_lst, ft_lstnew(cmd));
	}
	return (cmd_lst);
}
