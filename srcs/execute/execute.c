/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:49:34 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/20 16:43:28 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char
	*get_cmd(char **cmd, char *path)
{
	char		**paths;
	int			i;
	char		*cmd_name;
	struct stat	buff;

	buff.st_mode = 0;
	paths = ft_split(path, ':');
	free(path);
	i = 0;
	cmd_name = 0;
	while (paths[i])
	{
		cmd_name = ft_strjoin(paths[i], "/");
		cmd_name = ft_ownrealloc(&ft_strjoin, &cmd_name, *cmd);
		stat(cmd_name, &buff);
		if (buff.st_mode != 0)
			break ;
		i++;
		free(cmd_name);
	}
	ft_wordtab_clear(paths);
	if (buff.st_mode)
		return (cmd_name);
	return (validate_cmd(*cmd, buff, paths[0]));
}

static pid_t
	cmd_bin(char **args, t_list *envlst, char *cnd)
{
	pid_t	ret;
	char	**env;
	char	*cmd;

	if (exceptions(cnd))
		return (0);
	env = getallenv(envlst);
	cmd = get_cmd(args, ft_getenv("PATH", envlst));
	ret = (cmd) ? fork() : -1;
	if (ret == 0)
	{
		if (execve(cmd, args, env) == -1)
			exit(0);
	}
	ft_wordtab_clear(env);
	if (cmd && ft_strncmp(args[0], cmd, ft_strlen(cmd) + 1))
		free(cmd);
	return (ret);
}

static pid_t
	cmd_exec(char **args, t_list *envlst, int pipe, t_cmd *cnd)
{
	char	*cmd;

	cmd = ft_strtolower(args[0]);
	if (*args == 0)
		return (validate_redirects(cnd));
	if (!ft_strncmp(cmd, "echo", 5))
		g_struct.error = ft_echo(args);
	else if (!ft_strncmp(cmd, "cd", 3))
		g_struct.error = ft_cd(args, envlst, pipe);
	else if (!ft_strncmp(cmd, "env", 4) && !args[1])
		g_struct.error = ft_env(envlst);
	else if (!ft_strncmp(cmd, "exit", 5))
		g_struct.error = ft_exit(args);
	else if (!ft_strncmp(cmd, "export", 7))
		g_struct.error = ft_export(args, envlst, pipe);
	else if (!ft_strncmp(cmd, "pwd", 4))
		g_struct.error = ft_pwd(args);
	else if (!ft_strncmp(cmd, "unset", 6))
		ft_unset(args, &envlst, pipe);
	else
		return (cmd_bin(args, envlst, cmd));
	free(cmd);
	return (0);
}

static void
	pipe_loop(t_list *pipe_lst, t_fdstruct *fds, t_list *envlst, t_bool *l_cm)
{
	t_cmd	*cmd;
	int		h;

	g_struct.pid_count = 0;
	h = 0;
	while (pipe_lst)
	{
		cmd = pipe_lst->content;
		pipe_lst = pipe_lst->next;
		*l_cm = (!pipe_lst) ? TRUE : FALSE;
		if (!cmd || !(cmd->args)[0])
			check_cmd(cmd);
		else
		{
			set_fds(fds, cmd, *l_cm);
			g_struct.pid[g_struct.pid_count++] =
				cmd_exec(cmd->args, envlst, *l_cm, cmd);
			*l_cm = (*l_cm && !ft_strncmp((cmd->args)[0], "exit", 5)) ? 1 : 0;
		}
	}
	waitpid(g_struct.pid[g_struct.pid_count - 1], &h, 0);
	if (g_struct.error != 130 && g_struct.error != 131 &&
		g_struct.pid[g_struct.pid_count - 1] > 0)
		g_struct.error = h / 256;
}

void
	exec(t_list *cmd_lst, t_list *envlst, char *dir_add)
{
	t_fdstruct	fds;
	t_list		*pipe_lst;
	t_bool		l_cmd;

	while (cmd_lst)
	{
		pipe_lst = cmd_lst->content;
		pipe_lst = parse_pipes(pipe_lst, envlst, dir_add);
		init_fd(&fds);
		pipe_loop(pipe_lst, &fds, envlst, &l_cmd);
		ft_lstclear(&pipe_lst, &cmd_clears);
		unset_fd(&fds);
		if (l_cmd)
			break ;
		cmd_lst = cmd_lst->next;
	}
	free(dir_add);
}
