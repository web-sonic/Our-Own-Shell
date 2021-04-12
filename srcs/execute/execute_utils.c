/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exexcute_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 19:21:36 by sgath             #+#    #+#             */
/*   Updated: 2021/04/12 19:21:50 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int
	pipe_loop(t_list *pipe_lst, t_fdstruct *fds, t_list *envlst,
	char *dir_add)
{
	t_bool	l_cmd;
	t_cmd	*cmd;

	while (pipe_lst)
	{
		cmd = parser(pipe_lst->content, envlst, dir_add);
		pipe_lst = pipe_lst->next;
		if (!cmd)
			continue ;
		l_cmd = (!pipe_lst) ? TRUE : FALSE;
		set_fds(fds, cmd, l_cmd);
		if (cmd_exec(cmd->args, envlst, l_cmd, cmd))
			error_parse(PARSE_ERROR, 0);
		l_cmd = (l_cmd && !ft_strncmp((cmd->args)[0], "exit", 5)) ? 1 : 0;
		cmd_clear(cmd);
	}
	return (l_cmd);
}