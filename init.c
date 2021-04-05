/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:29:47 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/05 12:15:26 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
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

static void
	check_value_lst(t_env **envt, int *oldpwd)
{
	int	lvl;

	if (!ft_strncmp("SHLVL", (*envt)->val, 6))
	{
		lvl = ft_atoi((*envt)->arg);
		free((*envt)->arg);
		(*envt)->arg = 0;
		(*envt)->arg = ft_itoa(lvl + 1);
	}
	if (!ft_strncmp("OLDPWD", (*envt)->val, 7))
	{
		*oldpwd = 1;
		free((*envt)->arg);
		(*envt)->arg = 0;
		(*envt)->equally = 0;
	}
}

void
	init_envlist(t_list **envlst, char **env)
{
	int		i;
	int		oldpwd;
	t_env	*envt;

	i = -1;
	oldpwd = 0;
	while (env[++i])
	{
		envt = malloc(sizeof(t_env));
		line_split(envt, env[i], 0);
		check_value_lst(&envt, &oldpwd);
		ft_lstadd_back(envlst, ft_lstnew(envt));
	}
	create_oldpwd(envlst, oldpwd);
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
