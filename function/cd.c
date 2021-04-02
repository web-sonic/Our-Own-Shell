/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:15:08 by sgath             #+#    #+#             */
/*   Updated: 2021/04/02 17:34:00 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char
	*find_in_lst(t_list *envlst, char *name)
{
	t_env	*envt;

	while (envlst)
	{
		envt = envlst->content;
		if (!ft_strncmp(envt->val, name, ft_strlen(name) + 1))
			return (envt->arg);
		envlst = envlst->next;
	}
	return (NULL);
}

static int
	check_dir(t_list *envlst, char *dir_add, char *old_line)
{
	t_list	*pwd_lst;
	t_env	*envt;
	char	*dir_pwd;

	if (chdir(dir_add) == -1)
		cd_error(dir_add, old_line);
	pwd_lst = envlst;
	dir_pwd = ft_calloc(sizeof(char), PATH_MAX);
	getcwd(dir_pwd, PATH_MAX - 1);
	while (pwd_lst)
	{
		envt = pwd_lst->content;
		if (!ft_strncmp(envt->val, "PWD", 4))
			dub_and_free(&(envt->arg), dir_add);
		if (!ft_strncmp(envt->val, "OLDPWD", 7))
		{
			dub_and_free(&(envt->arg), dir_pwd);
			envt->equally = 1;
		}
		pwd_lst = pwd_lst->next;
	}
	free(dir_pwd);
	return (0);
}

static int
	ret_dir(t_list *envlst, char *name)
{
	char	*dir_add;

	dir_add = find_in_lst(envlst, name);
	if (!dir_add)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(" not set", 2);
		return (1);
	}
	return (check_dir(envlst, dir_add, 0));
}

static int
	full_dir(t_list *envlst, char *dir_add)
{
	char	*dir_pwd;
	int		rez;

	if (dir_add[0] != '/')
	{
		dir_pwd = ft_calloc(sizeof(char), PATH_MAX);
		getcwd(dir_pwd, PATH_MAX - 1);
		dir_pwd = ft_ownrealloc(&ft_strjoin, &dir_pwd, "/");
		dir_pwd = ft_ownrealloc(&ft_strjoin, &dir_pwd, dir_add);
	}
	else
		dir_pwd = ft_strdup(dir_add);
	rez = check_dir(envlst, dir_pwd, dir_add);
	free(dir_pwd);
	return (rez);
}

int
	ft_cd(char **line, t_list *envlst)
{
	int		rez;
	char	*tmp;

	rez = -1;
	if (!line[1])
		return (ret_dir(envlst, "HOME"));
	if (rez == -1 && !ft_strncmp(line[1], "-", 2))
		rez = ret_dir(envlst, "OLDPWD");
	if (rez == -1 && !ft_strncmp(line[1], "--", 3))
		rez = ret_dir(envlst, "HOME");
	tmp = line[1];
	if (rez == -1)
		rez = full_dir(envlst, tmp);
	return (rez);
}
