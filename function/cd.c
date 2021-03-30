/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:36 by sgath             #+#    #+#             */
/*   Updated: 2021/03/29 23:59:27 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int
	no_arg(t_list **envlst)
{
	t_list	*tmp_lst;
	t_env	*enviroment;

	tmp_lst = *envlst;
	while (tmp_lst)
	{
		enviroment = tmp_lst->content;
		if(!ft_strncmp(enviroment->value, "HOME", 5))
		{
			check_dir(envlst,enviroment->argum, 0);
			return (1);
		}
	}
	ft_putendl_fd("minishell> cd: HOME not set", 1);
	return (1);
}

static int
	two_dot(t_list **envlst)
{
	char	*dir;
	int		len;

	dir = ft_calloc(sizeof(char), PATH_MAX);
	getcwd(dir, PATH_MAX - 1);
	len = ft_strlen(dir);
	len--;
	while(dir[--len] != '/')
		dir[len] = '\0';
	check_dir(envlst, dir, 0);
	free(dir);
	return (1);
}

static int
	divis(t_list **envlst, int count)
{
	t_list	*tmp_lst;
	t_env	*enviroment;

	tmp_lst = *envlst;
	while (tmp_lst)
	{
		enviroment = tmp_lst->content;
		if(!ft_strncmp(enviroment->value, "OLDPWD", 7))
		{
			check_dir(envlst,enviroment->argum, count);
			return (1);
		}
	}
	ft_putendl_fd("minishell> cd: OLDPWD not set", 1);
	return (1);
}

void
	check_dir(t_list **envlst, char *dir_add, int count)
{
	t_list	*pwd_lst;
	t_env	*enviroment;
	char	*dir_pwd;

	dir_pwd = ft_calloc(sizeof(char), PATH_MAX);
	getcwd(dir_pwd, PATH_MAX - 1);
	if (chdir(dir_add) < 0)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(dir_add, 1);
		ft_putstr_fd(": No such file or directory", 1);
	}
	else
	{
		pwd_lst = *envlst;
		while (pwd_lst)
		{
			enviroment = pwd_lst->content;
			if(!ft_strncmp(enviroment->value, "PWD", 4))
				dub_and_free(enviroment->argum, dir_add);
			if(!ft_strncmp(enviroment->value, "OLDPWD", 4))
			{
				if (count == 1 && enviroment->argum)
					ft_putendl_fd(enviroment->argum, 1);
				dub_and_free(enviroment->argum, dir_pwd);
			}
			pwd_lst = pwd_lst->next;
		}
		
	}
	free(dir_pwd);
}

void
	ft_cd(char **line, t_list **envlst)
{
	int		rez;

	rez = 0;
	if (!line[0])
		rez = no_arg(envlst);
	if (rez == 0 && !ft_strncmp(line[0], ".", 2))
		return;
	if (rez == 0 && !ft_strncmp(line[0], "..", 3))
		rez = two_dot(envlst);
	if (rez == 0 && !ft_strncmp(line[0], "-", 2))
		rez = divis(envlst, 2);
	if (rez == 0 && !ft_strncmp(line[0], "--", 3))
		rez = divis(envlst, 2);
	else
		check_dir(envlst, line[0], 0);
}
