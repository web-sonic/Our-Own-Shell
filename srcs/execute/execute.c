/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:49:34 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/19 17:27:20 by ctragula         ###   ########.fr       */
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
	int		h;

	h = 0;
	free(cnd);
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
		return (cmd_bin(args, envlst, cmd));
	free(cmd);
	return (0);
}

static int
	pipe_loop(t_list *pipe_lst, t_fdstruct *fds, t_list *envlst)
{
	t_bool	l_cmd;
	t_cmd	*cmd;
	pid_t	ret;
	int		h;

	ret = 0;
	while (pipe_lst)
	{
		cmd = pipe_lst->content;
		pipe_lst = pipe_lst->next;
		l_cmd = (!pipe_lst) ? TRUE : FALSE;
		set_fds(fds, cmd, l_cmd);
		if (!(cmd->args)[0])
			break ;
		ret = cmd_exec(cmd->args, envlst, l_cmd, cmd);
		l_cmd = (l_cmd && !ft_strncmp((cmd->args)[0], "exit", 5)) ? 1 : 0;
		cmd_clear(cmd);
	}
	waitpid(ret, &h, 0);
	if (ret > 0 && g_error != 130 && g_error != 131)
		g_error = h / 256;
	return (l_cmd);
}

static t_list
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
	return cmd_lst;
}

void
	exec(t_list *cmd_lst, t_list *envlst, char *dir_add)
{
	t_fdstruct	fds;
	t_list		*pipe_lst;

	while (cmd_lst)
	{
		pipe_lst = cmd_lst->content;
		pipe_lst = parse_pipes(pipe_lst, envlst, dir_add);
		init_fd(&fds);
		if (pipe_loop(pipe_lst, &fds, envlst))
			break ;
		unset_fd(&fds);
		cmd_lst = cmd_lst->next;
	}
	free(dir_add);
}
