/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:49:34 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/31 16:38:11 by ctragula         ###   ########.fr       */
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

t_cmd
	*cmd_clear(t_cmd *cmd)
{
	if (cmd->args)
		ft_wordtab_clear(cmd->args);
	free(cmd);
	return (0);
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
	{
		ft_wordtab_clear(paths);
		return (cmd_name);
	}
	ft_wordtab_clear(paths);
	return (cmd);
}

void
	cmd_bin(char **args, t_list *envlst)
{
	pid_t	ret;
	char	**env;
	char	*cmd;
	int		h;

	ret = fork();
	env = getallenv(envlst);
	cmd = get_cmd(args[0], ft_getenv("PATH", envlst));
	if (ret == 0)
	{
		execve(cmd, args, env);
		exit(errno);
	}
	else
		waitpid(ret, &h, 0);
	g_error = h / 256;
	ft_wordtab_clear(env);
	if (ft_strncmp(args[0], cmd, ft_strlen(cmd) + 1))
		free(cmd);
}

int
	cmd_execute(char **args, t_list *envlst, char *dir_add)
{
	if (*args == 0)
	{
		free(*args);
		return (1);
	}
	else if (!ft_strncmp(args[0], "echo", 5))
		ft_echo(args);
	else if (!ft_strncmp(args[0], "cd", 3))
		g_error = ft_cd(args, &envlst, dir_add);
	else if (!ft_strncmp(args[0], "env", 4))
		ft_env(&envlst);
	else if (!ft_strncmp(args[0], "exit", 5))
		ft_exit(args);
	else if (!ft_strncmp(args[0], "export", 7))
		ft_export(args, envlst);
	else if (!ft_strncmp(args[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(args[0], "unset", 6))
		ft_unset(args, &envlst);
	else
		cmd_bin(args, envlst);
	return (0);
}

void
	execute(t_list *cmd_lst, t_list *envlst, char *dir_add)
{
	t_cmd		*cmd;
	t_fdstruct	fds;
	t_bool		last_cmd;
	t_list		*pipe_lst;

	while (cmd_lst)
	{
		pipe_lst = cmd_lst->content;
		init_fd(&fds);
		last_cmd = FALSE;
		while (pipe_lst)
		{
			if (!(cmd = parser(pipe_lst->content, envlst)))
				break ;
			pipe_lst = pipe_lst->next;
			if (!pipe_lst)
				last_cmd = TRUE;
			set_fds(&fds, cmd, last_cmd);
			if (cmd_execute(cmd->args, envlst, dir_add))
				error_parse(PARSE_ERROR, 0);
			cmd_clear(cmd);
		}
		unset_fd(&fds);
		cmd_lst = cmd_lst->next;
	}
}
