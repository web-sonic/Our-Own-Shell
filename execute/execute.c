/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 13:49:34 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/02 14:04:15 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void
	set_fds(t_fdstruct *fds, t_cmd *cmd, t_bool last_cmd)
{
	int	fdpipe[2];

	if (cmd->is_fdin)
	{
		dup2(cmd->fdin, 0);
		close(cmd->fdin);
	}
	else
		dup2(fds->fdin, 0);
	if (last_cmd)
	{
		close(fds->fdin);
		(cmd->is_fdout) ? fds->fdout = dup(cmd->fdout) :
			(fds->fdout = dup(fds->tmpout));
	}
	else
	{
		pipe(fdpipe);
		fds->fdin = fdpipe[0];
		fds->fdout = fdpipe[1];
	}
	if (!cmd->is_fdout)
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
	close(fds->fdin);
	close(fds->fdout);
}

void	ft_wordtab_clears(char **tab_lst)
{
	int	count;

	count = 0;
	while (tab_lst[count])
	{
		free(tab_lst[count]);
		count++;
	}
	free(tab_lst[count]);
	free(tab_lst);
}

t_cmd
	*cmd_clear(t_cmd *cmd)
{
	if (cmd->args)
		ft_wordtab_clears(cmd->args);
	close(cmd->fdin);
	close(cmd->fdout);
	cmd->fdin = 0;
	cmd->fdout = 0;
	cmd->is_fdin = FALSE;
	cmd->is_fdout = FALSE;
	free(cmd);
	return (0);
}

char
	*get_cmd(char **cmd, char *path)
{
	char	**paths;
	int		i;
	char	*cmd_name;
	struct	stat buff;

	paths = ft_split(path, ':');
	free(path);
	i = 0;
	while (paths[i])
	{
		cmd_name = ft_strjoin(paths[i], "/");
		cmd_name = ft_ownrealloc(&ft_strjoin, &cmd_name, *cmd);
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
	return (*cmd);
}

void
	print_error2(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (strchr(str, '/'))
	{
		if (open(str, O_RDONLY | O_DIRECTORY) >= 0)
		{
			ft_putendl_fd("is directory.", 2);
			g_error = 126;
		}
		else if (open(str, O_RDWR) < 0)
		{
			ft_putendl_fd(strerror(errno), 1);
			g_error = 127;
		}
		else
		{
			ft_putendl_fd("Permission denied", 2);
			g_error = 126;
		}
	}
	else
	{
		ft_putendl_fd("command not found", 1);
		g_error = 127;
	}
}

void
	cmd_bin(char **args, t_list *envlst)
{
	pid_t	ret;
	char	**env;
	char	*cmd;
	int		h;

	h = 0;
	env = getallenv(envlst);
	cmd = get_cmd(args, ft_getenv("PATH", envlst));
	ret = fork();
	if (ret == 0)
	{
		execve(cmd, args, env);
		exit(errno);
	}
	else
		waitpid(ret, &h, 0);
	ft_wordtab_clear(env);
	g_error = h / 256;
	if (cmd && ft_strncmp(args[0], cmd, ft_strlen(cmd) + 1))
		free(cmd);
	if (g_error > 1 && g_error != 126 && g_error != 127)
		print_error2(args[0]);	
}

void
	exceptions(char c)
{
	if (c == '.')
	{
		g_error = 2;
		ft_putendl_fd("minishell: .: filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
	}
	else
	{
		g_error = 126;
		ft_putendl_fd("minishell: /Users: is a directory", 2);
	}
}

char
	*ft_strtolower(char *str)
{
	size_t	i;
	char	*new_str;
	
	new_str = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	i = 0;
	while (str[i])
	{
		new_str[i] = ft_tolower(str[i]);
		i++;
	}
	return (new_str);
}

int
	validate_redirects(t_cmd *cmd)
{
	if (cmd->is_fdin || cmd->is_fdout)
		return (0);
	return (1);
}

int
	cmd_execute(char **args, t_list *envlst, int pipe, t_cmd *cnd)
{
	char	*cmd;

	if (*args == 0)
		return (validate_redirects(cnd));
	cmd = ft_strtolower(args[0]);
	if (!ft_strncmp(cmd, "echo", 5))
		g_error = ft_echo(args);
	else if (!ft_strncmp(cmd, "cd", 3))
		g_error = ft_cd(args, envlst);
	else if (!ft_strncmp(cmd, "env", 4))
		g_error = ft_env(&envlst);
	else if (!ft_strncmp(cmd, "exit", 5))
		g_error = ft_exit(args);
	else if (!ft_strncmp(cmd, "export", 7))
		g_error = ft_export(args, envlst, pipe);
	else if (!ft_strncmp(cmd, "pwd", 4))
		g_error = ft_pwd();
	else if (!ft_strncmp(cmd, "unset", 6))
		g_error = ft_unset(args, &envlst, pipe);
	else if (!ft_strncmp(args[0], ".", 2) || !ft_strncmp(args[0], "/Users", 7))
		exceptions(args[0][0]);
	else
		cmd_bin(args, envlst);
	free(cmd);
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
		while (pipe_lst && (cmd = parser(pipe_lst->content, envlst, dir_add)))
		{
			pipe_lst = pipe_lst->next;
			last_cmd = (!pipe_lst) ? TRUE : FALSE;
			set_fds(&fds, cmd, last_cmd);
			if (cmd_execute(cmd->args, envlst, last_cmd, cmd))
				error_parse(PARSE_ERROR, 0);
			cmd_clear(cmd);
		}
		if (!cmd)
			break ;
		unset_fd(&fds);
		cmd_lst = cmd_lst->next;
	}
	free(dir_add);
}
