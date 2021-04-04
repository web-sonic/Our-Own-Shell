/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:15:08 by sgath             #+#    #+#             */
/*   Updated: 2021/04/04 14:13:09 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void
	add_env(t_list *envlst, char *dir_pwd)
{
	t_list	*pwd_lst;
	t_env	*envt;

	pwd_lst = envlst;
	while (pwd_lst)
	{
		envt = pwd_lst->content;
		if (!ft_strncmp(envt->val, "OLDPWD", 7))
		{
			dub_and_free(&(envt->arg), dir_pwd);
			envt->equally = 1;
		}
		pwd_lst = pwd_lst->next;
	}
	pwd_lst = envlst;
	while (pwd_lst)
	{
		envt = pwd_lst->content;
		if (!ft_strncmp(envt->val, "PWD", 4))
		{
			getcwd(dir_pwd, PATH_MAX - 1);
			dub_and_free(&(envt->arg), dir_pwd);
		}
		pwd_lst = pwd_lst->next;
	}
}

static int
	check_dir(t_list *envlst, char *dir_add, char *old_line, int pipe)
{
	char	*dir_pwd;

	dir_pwd = ft_calloc(sizeof(char), PATH_MAX);
	getcwd(dir_pwd, PATH_MAX - 1);
	if (chdir(dir_add) == -1)
		return (cd_error(dir_add, old_line));
	pipe == 1 ? add_env(envlst, dir_pwd) : chdir(dir_pwd);
	free(dir_pwd);
	return (0);
}

static int
	ret_dir(t_list *envlst, int pipe, char *name)
{
	char	*dir_add;
	t_list	*tmp_lst;
	t_env	*envt;

	dir_add = NULL;
	tmp_lst = envlst;
	while (tmp_lst)
	{
		envt = tmp_lst->content;
		if (!ft_strncmp(envt->val, name, ft_strlen(name) + 1))
			dir_add = envt->arg;
		tmp_lst = tmp_lst->next;
	}
	if (!dir_add)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(" not set", 2);
		return (1);
	}
	return (check_dir(envlst, dir_add, 0, pipe));
}

static int
	full_dir(t_list *envlst, char *dir_add, int pipe)
{
	char	*dir_pwd;
	int		rez;

	if (!ft_strncmp(dir_add, "..", 3))
		dir_pwd = ft_strdup(dir_add);
	else if (dir_add[0] != '/')
	{
		dir_pwd = ft_calloc(sizeof(char), PATH_MAX);
		getcwd(dir_pwd, PATH_MAX - 1);
		dir_pwd = ft_ownrealloc(&ft_strjoin, &dir_pwd, "/");
		dir_pwd = ft_ownrealloc(&ft_strjoin, &dir_pwd, dir_add);
	}
	else
		dir_pwd = ft_strdup(dir_add);
	rez = check_dir(envlst, dir_pwd, dir_add, pipe);
	free(dir_pwd);
	return (rez);
}

int
	ft_cd(char **line, t_list *envlst, int pipe)
{
	int		rez;
	char	*tmp;

	rez = -1;
	if (!line[1])
		return (ret_dir(envlst, pipe, "HOME"));
	if (!ft_strncmp(line[1], ".", 2))
		rez = 0;
	if (rez == -1 && !ft_strncmp(line[1], "-", 2))
		rez = ret_dir(envlst, pipe, "OLDPWD");
	if (line[1][0] == '-' && line[1][1] != 0)
		rez = flag_error(line[0], line[1]);
	if (rez == -1 && !ft_strncmp(line[1], "--", 3))
		rez = ret_dir(envlst, pipe, "HOME");
	tmp = line[1];
	if (rez == -1)
		rez = full_dir(envlst, tmp, pipe);
	return (rez);
}
