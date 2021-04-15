/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:49:34 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/15 17:12:14 by sgath            ###   ########.fr       */
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

static void
	cmd_bin(char **args, t_list *envlst)
{
	pid_t	ret;
	char	**env;
	char	*cmd;
	int		h;

	h = 0;
	env = getallenv(envlst);
	cmd = get_cmd(args, ft_getenv("PATH", envlst));
	ret = (cmd) ? fork() : -1;
	if (ret == 0)
	{
		if (execve(cmd, args, env) == -1)
			exit(0);
	}
	else if (ret > 0)
		wait(&h);
	ft_wordtab_clear(env);
	if (ret > 0 && g_error != 130 && g_error != 131)
		g_error = h / 256;
	if (cmd && ft_strncmp(args[0], cmd, ft_strlen(cmd) + 1))
		free(cmd);
}

static int
	cmd_exec(char **args, t_list *envlst, int pipe, t_cmd *cnd)
{
	char	*cmd;

	if (*args == 0)
		return (validate_redirects(cnd));
	cmd = ft_strtolower(args[0]);
	if (!ft_strncmp(cmd, "echo", 5))
		g_error = ft_echo(args);
	else if (!ft_strncmp(cmd, "cd", 3))
		g_error = ft_cd(args, envlst, pipe);
	else if (!ft_strncmp(cmd, "env", 4) && !args[1])
		g_error = ft_env(envlst);
	else if (!ft_strncmp(cmd, "exit", 5))
		g_error = ft_exit(args);
	else if (!ft_strncmp(cmd, "export", 7))
		g_error = ft_export(args, envlst, pipe);
	else if (!ft_strncmp(cmd, "pwd", 4))
		g_error = ft_pwd(args);
	else if (!ft_strncmp(cmd, "unset", 6))
		ft_unset(args, &envlst, pipe);
	else if (!ft_strncmp(args[0], ".", 2) || !ft_strncmp(args[0], "/Users", 7)
		|| !ft_strncmp(args[0], "/", 2))
		exceptions(args[0]);
	else
		cmd_bin(args, envlst);
	free(cmd);
	return (0);
}

static int
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
		if (!(cmd->args)[0])//#не сегается, но >1 виснет
			break ;
		l_cmd = (l_cmd && !ft_strncmp((cmd->args)[0], "exit", 5)) ? 1 : 0;
		cmd_clear(cmd);
	}
	return (l_cmd);
}

void
	exec(t_list *cmd_lst, t_list *envlst, char *dir_add)
{
	t_fdstruct	fds;
	t_list		*pipe_lst;

	while (cmd_lst)
	{
		pipe_lst = cmd_lst->content;
		init_fd(&fds);
		if (pipe_loop(pipe_lst, &fds, envlst, dir_add))
			break ;
		unset_fd(&fds);
		cmd_lst = cmd_lst->next;
	}
	free(dir_add);
}
