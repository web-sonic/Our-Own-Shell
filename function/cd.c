/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:36 by sgath             #+#    #+#             */
/*   Updated: 2021/03/30 16:31:10 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void
	check_dir(t_list **envlst, char *dir_add, int count)
{
	t_list	*pwd_lst;
	t_env	*enviroment;
	char	*dir_pwd;
	char	*dir_cd;
	int		ret;

	//dir_cd = ft_strdup(dir_add);
	dir_pwd = ft_calloc(sizeof(char), PATH_MAX);
	getcwd(dir_pwd, PATH_MAX - 1);
	ret = chdir(dir_add);
	if (ret == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(dir_add, 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit (1);
	}
	else
	{
		pwd_lst = *envlst;
		while (pwd_lst)
		{
			enviroment = pwd_lst->content;
			if(!ft_strncmp(enviroment->value, "PWD", 4))
			{
				dub_and_free(&(enviroment->argum), dir_add);
				ft_putendl_fd(enviroment->argum, 1);
			}
			if(!ft_strncmp(enviroment->value, "OLDPWD", 7))
			{
				if (count == 1 && enviroment->argum)
					ft_putendl_fd(enviroment->argum, 1);
				dub_and_free(&(enviroment->argum), dir_pwd);
			}
			pwd_lst = pwd_lst->next;
		}
		
	}
	free(dir_pwd);
	ft_putstr_fd(getcwd(dir_pwd, PATH_MAX - 1), 1);
}

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
			return (0);
		}
		tmp_lst = tmp_lst->next;
	}
	ft_putendl_fd("minishell: cd: HOME not set", 2);
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
			return (0);
		}
	}
	ft_putendl_fd("minishell: cd: OLDPWD not set", 1);
	exit(1);
}

void
	ft_cd(char **line, t_list **envlst)
{
	if (!line[1])
		no_arg(envlst);
	if (!ft_strncmp(line[1], ".", 2))
		exit (0);	
	if (!ft_strncmp(line[1], "..", 3))
		two_dot(envlst);
	if (!ft_strncmp(line[1], "-", 2))
		divis(envlst, 2);
	if (!ft_strncmp(line[1], "--", 3))
		divis(envlst, 2);
	else
		check_dir(envlst, line[1], 0);
}
