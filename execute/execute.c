/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:49:34 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/30 13:23:59 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void
	set_fds(t_fdstruct *fds, t_cmd *cmd, t_bool last_cmd)
{
	int	fdpipe[2];

	if (cmd->fdin)
	{
		dup2(cmd->fdin, 0);
		close(cmd->fdin);
		close(fds->fdin);
	}
	else
	{
		dup2(fds->fdin, 0);
		close(fds->fdin);
	}
	if (last_cmd)
	{
		(cmd->fdout) ? fds->fdout = dup(cmd->fdout) :
			(fds->fdout = dup(fds->tmpout));
	}
	else
	{
		pipe(fdpipe);
		fds->fdin = fdpipe[0];
		fds->fdout = fdpipe[1];
	}
	if (!cmd->fdout)
	{
		dup2(fds->fdout, 1);
		close(fds->fdout);
	}
	else
	{
		dup2(cmd->fdout, 1);
		close(fds->fdout);
		close(cmd->fdout);
	}
}

static void
	init_fd(t_fdstruct *fds)
{
	fds->tmpin = dup(0);
	fds->tmpout = dup(1);
	fds->fdin = dup(fds->tmpin);
	fds->fdout = dup(fds->tmpout);
}

void
	unset_fd(t_fdstruct *fds)
{
	dup2(fds->tmpin, 0);
	dup2(fds->tmpout, 1);
	close(fds->tmpin);
	close(fds->tmpout);
}

void
	cmd_clear(t_cmd *cmd)
{
	ft_wordtab_clear(cmd->args);
	free(cmd);
}

int
	cmd_execute(char **args, t_fdstruct	*fds, t_list *envlst)
{
	pid_t	ret;

	ret = fork();
	if (ret == 0)
	{
		if (!ft_strncmp(args[0], "echo", 5))
			ft_echo(args);
		if (!ft_strncmp(args[0], "cd", 3))
			ft_cd(args);
		if (!ft_strncmp(args[0], "env", 4))
			ft_env(args);
		if (!ft_strncmp(args[0], "exit", 5))
			ft_exit(&g_error, args);
		if (!ft_strncmp(args[0], "export", 7))
			ft_export(args, envlst);
		if (!ft_strncmp(args[0], "pwd", 4))
			ft_pwd();
		if (!ft_strncmp(args[0], "unset", 6))
			ft_unset(args[0], envlst);
		exit(0);
	}
	else if (ret == -1)
	{
		ft_putendl_fd("nope", 1);
		return (ret);
	}
	else
		return (ret);	
}

void
	execute(t_list *cmd_lst, t_list *envlst)
{
	t_cmd		*cmd;
	t_fdstruct	fds;
	t_bool		last_cmd;
	t_list		*pipe_lst;
	pid_t		ret;

	while (cmd_lst)
	{
		pipe_lst = cmd_lst->content;
		init_fd(&fds);
		last_cmd = FALSE;
		while (pipe_lst)
		{
			cmd = parser(pipe_lst->content, envlst);
			pipe_lst = pipe_lst->next;
			if (!pipe_lst)
				last_cmd = TRUE;
			set_fds(&fds, cmd, last_cmd);
			ret = cmd_execute(cmd->args, &fds, envlst);
			cmd_clear(cmd);
		}
		unset_fd(&fds);
		waitpid(ret, NULL, 0);
		cmd_lst = cmd_lst->next;
	}
}
