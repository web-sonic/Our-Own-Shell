/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:47:22 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/03 20:25:01 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	*get_homepath(void)
{
	char	*dir;
	char	*str;
	char	**way;

	way = 0;
	str = ft_strdup("/tmp/.minishell_history");
	dir = ft_calloc(sizeof(char), PATH_MAX);
	if (getcwd(dir, PATH_MAX - 1))
	{
		way = ft_split(dir, '/');
		if (way[1] && !ft_strncmp(way[0], "Users", 6))
		{
			free(str);
			str = ft_strjoin("/Users/", way[1]);
			str = ft_ownrealloc(&ft_strjoin, &str, "/.minishell_history");
		}
	}
	ft_wordtab_clear(way);
	free(dir);
	return (str);
}

static void
	init_histlist(t_dlist **histlist, char *dir_add)
{
	int		fd;
	int		i;
	char	*line;

	*histlist = 0;
	fd = open(dir_add, O_RDONLY | O_CREAT, 0755);
	if (fd < 0)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	while ((i = get_next_line(fd, &line)) > 0)
	{
		if (line[0] != '\0')
			ft_dlstadd_back(histlist, ft_dlstnew(line));
		else
			free(line);
	}
	free(line);
	if (i == -1)
		exit(1);
	close(fd);
}

void
	create_oldpwd(t_list **envlst, int oldpwd)
{
	t_env	*envt;

	if (oldpwd == 0)
	{
		envt = malloc(sizeof(t_env));
		envt->val = ft_strdup("OLDPWD");
		envt->arg = NULL;
		envt->equally = 0;
		ft_lstadd_back(envlst, ft_lstnew(envt));
	}
}

void
	init_envlist(t_list **envlst, char **env)
{
	int		i;
	int		lvl;
	int		oldpwd;
	t_env	*envt;

	i = -1;
	oldpwd = 0;
	while (env[++i])
	{
		envt = malloc(sizeof(t_env));
		line_split(envt, env[i], 0);
		if (!ft_strncmp("SHLVL", envt->val, 6))
		{
			lvl = ft_atoi(envt->arg);
			free(envt->arg);
			envt->arg = ft_itoa(lvl + 1);
		}
		if (!ft_strncmp("OLDPWD", envt->val, 7))
		{
			oldpwd = 1;
			free(envt->arg);
			envt->equally = 0;
		}
		ft_lstadd_back(envlst, ft_lstnew(envt));
	}
	create_oldpwd(envlst, oldpwd);
}

static int
	empty_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && ft_strchr(SPACES, line[i]))
		i++;
	if (!line[i])
	{
		g_error = 0;
		if (!i)
			free(line);
		return (1);
	}
	return (0);
}

void
	clear_doublelst(void *content)
{
	t_list	*lst;

	lst = content;
	ft_lstclear(&lst, &free);
}

void
	shell(t_dlist **histlist, t_list *envlst, char *dir_add)
{
	char	*line;
	t_list	*cmd_lst;
	t_list	*magic_lst;

	magic_lst = 0;
	line = readline(histlist, dir_add);
	if (line && !empty_line(line))
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		cmd_lst = get_cmds(line, &magic_lst);
		if (cmd_lst)
		{
			execute(cmd_lst, envlst, mod_address(dir_add));
			ft_lstclear(&cmd_lst, &clear_doublelst);
		}
	}
	if (magic_lst)
		ft_lstclear(&magic_lst, &free);
}

int
	main(int argc, char **argv, char **env)
{
	t_dlist	*histlist;
	char	*dir_add;
	t_list	*envlst;

	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, &signal_handler);
	dir_add = get_homepath();
	init_histlist(&histlist, dir_add);
	init_envlist(&envlst, env);
	(void)argv[0];
	while (argc)
		shell(&histlist, envlst, dir_add);
	return (0);
}
