/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:49:34 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/30 21:08:27 by ctragula         ###   ########.fr       */
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

char
	*get_cmd(char *cmd, char *path)
{
	char	**paths;
	int		i;
	char	*cmd_name;
	struct	stat buff;

	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		cmd_name = ft_strjoin(paths[i], "/");
		cmd_name = ft_ownrealloc(&ft_strjoin, &cmd_name, cmd);
		stat(cmd_name, &buff);
		if (buff.st_mode != 0)
			break;
		i++;
		free(cmd_name);
	}
	if (paths[i])
		return (cmd_name);
	else
		return (cmd);
}

int
	cmd_bin(char **args, t_list *envlst)
{
	pid_t	ret;
	char	**env;
	char	*cmd;

	ret = fork();
	env = getallenv(envlst);
	cmd = get_cmd(args[0], ft_getenv("PATH", envlst));
	if (ret == 0)
	{
		execve(cmd, args, env);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_error = (short)errno;
		exit(2);
	}
	else
		waitpid(ret, &g_error, 0);
	ft_wordtab_clear(env);
	free(cmd);
}

int
	cmd_execute(char **args, t_list *envlst)
{
	if (!ft_strncmp(args[0], "echo", 5))
		ft_echo(args);
	else if (!ft_strncmp(args[0], "cd", 3))
		ft_cd(args, &envlst);
	else if (!ft_strncmp(args[0], "env", 4))
		ft_env(&envlst);
	else if (!ft_strncmp(args[0], "exit", 5))
		ft_exit(args);
	else if (!ft_strncmp(args[0], "export", 7))
		ft_export(args, &envlst);
	else if (!ft_strncmp(args[0], "pwd", 4))
		ft_pwd();
//	else if (!ft_strncmp(args[0], "unset", 6))
//		ft_unset(args, &envlst);cd 
	else
		cmd_bin(args, envlst);
	return (0);
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
			ret = cmd_execute(cmd->args, envlst);
			cmd_clear(cmd);
		}
		unset_fd(&fds);
		cmd_lst = cmd_lst->next;
	}
}
