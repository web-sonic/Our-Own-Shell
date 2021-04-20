/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:29:47 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/20 13:04:43 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void
	create_lst(t_list **envlst, int flag)
{
	t_env	*envt;

	envt = malloc(sizeof(t_env));
	if (flag == 0)
	{
		envt->val = ft_strdup("OLDPWD");
		envt->arg = NULL;
		envt->equally = 0;
	}
	if (flag == 1)
	{
		envt->val = ft_strdup("SHLVL");
		envt->arg = ft_strdup("1");
		envt->equally = 1;
	}
	if (flag == 2)
	{
		envt->val = ft_strdup("PWD");
		envt->arg = ft_calloc(sizeof(char), PATH_MAX);
		getcwd(envt->arg, PATH_MAX - 1);
		envt->equally = 1;
	}
	ft_lstadd_back(envlst, ft_lstnew(envt));
}

static void
	check_value_lst(t_env **envt, int *oldpwd, int *shlvl, int *pwd)
{
	if (!ft_strncmp("SHLVL", (*envt)->val, 6))
		check_valid_shlvl(envt, shlvl);
	if (!ft_strncmp("OLDPWD", (*envt)->val, 7))
	{
		*oldpwd = 1;
		savefree((*envt)->arg);
		(*envt)->arg = 0;
		(*envt)->equally = 0;
	}
	if (!ft_strncmp("PWD", (*envt)->val, 4))
	{
		*pwd = 1;
		savefree((*envt)->arg);
		(*envt)->arg = 0;
		(*envt)->arg = ft_calloc(sizeof(char), PATH_MAX);
		getcwd((*envt)->arg, PATH_MAX - 1);
	}
}

void
	init_envlist(t_list **envlst, char **env)
{
	int		i;
	int		oldpwd;
	int		shlvl;
	int		pwd;
	t_env	*envt;

	i = -1;
	oldpwd = 0;
	shlvl = 0;
	pwd = 0;
	while (env[++i])
	{
		envt = malloc(sizeof(t_env));
		line_split(envt, env[i], 0);
		check_value_lst(&envt, &oldpwd, &shlvl, &pwd);
		ft_lstadd_back(envlst, ft_lstnew(envt));
	}
	if (oldpwd == 0)
		create_lst(envlst, 0);
	if (shlvl == 0)
		create_lst(envlst, 1);
	if (pwd == 0)
		create_lst(envlst, 2);
}

void
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

t_cmd
	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->args = ft_calloc(sizeof(char *), 1);
	(cmd->args)[0] = 0;
	cmd->fdin = -1;
	cmd->fdout = -1;
	cmd->add_fd = -1;
	cmd->is_fdin = FALSE;
	cmd->is_fdin = FALSE;
	return (cmd);
}
