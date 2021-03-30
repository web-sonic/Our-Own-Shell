/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:36 by sgath             #+#    #+#             */
/*   Updated: 2021/03/30 21:08:34 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int
	check_dir(t_list **envlst, char *dir_add, char *all_add)
{
	t_list		*pwd_lst;
	t_env		*enviroment;
	char		*dir_pwd;
	char		*add;
	int			rez;

	rez = 0;
	dir_pwd = ft_calloc(sizeof(char), PATH_MAX);
	getcwd(dir_pwd, PATH_MAX - 1);
	if (!all_add)
		add = ft_strdup(dir_add);
	else
		add = ft_strjoin (all_add, dir_add);
	if (chdir(add) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(dir_add, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		rez = 1;
	}
	else
	{
		pwd_lst = *envlst;
		while (pwd_lst)
		{
			enviroment = pwd_lst->content;
			if(!ft_strncmp(enviroment->value, "PWD", 4))
				dub_and_free(&(enviroment->argum), dir_add);
			if(!ft_strncmp(enviroment->value, "OLDPWD", 7))
				dub_and_free(&(enviroment->argum), dir_pwd);
			pwd_lst = pwd_lst->next;
		}
	}
	free(dir_pwd);
	free(add);
	return (rez);
}

static int
	home_arg(t_list **envlst)
{
	t_list	*tmp_lst;
	t_env	*enviroment;

	tmp_lst = *envlst;
	while (tmp_lst)
	{
		enviroment = tmp_lst->content;
		if(!ft_strncmp(enviroment->value, "HOME", 5))
		{
			return (check_dir(envlst,enviroment->argum, 0));
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
	int		rez;

	dir = ft_calloc(sizeof(char), PATH_MAX);
	getcwd(dir, PATH_MAX - 1);
	len = ft_strlen(dir);
	len--;
	while(len > 0 && dir[--len] != '/')
		dir[len] = '\0';
	rez = check_dir(envlst, dir, NULL);
	free(dir);
	return (rez);
}

static int
	divis(t_list **envlst)
{
	t_list	*tmp_lst;
	t_env	*enviroment;
	int rez;

	rez = 1;
	tmp_lst = *envlst;
	while (tmp_lst)
	{
		enviroment = tmp_lst->content;
		if(!ft_strncmp(enviroment->value, "OLDPWD", 7))
		{
			rez = check_dir(envlst, enviroment->argum, NULL);
			if (rez == 0)
				ft_putendl_fd(enviroment->argum, 1);
			return (rez);
		}
		tmp_lst = tmp_lst->next;
	}
	ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
	return (rez);
}

static int
	add_dir(t_list **envlst, char *add_dir, char *home_arg)
{
	char	*dir;
	int		rez;
	t_list	*tmp_lst;
	t_env	*enviroment;
	
	dir = NULL;
	tmp_lst = *envlst;
	if (add_dir[0] == '~')
	{
		while (tmp_lst)
		{
			enviroment = tmp_lst->content;
			if(!ft_strncmp(enviroment->value, "HOME", 5))
			{
				dir = ft_strdup(enviroment->argum);
				dir++;
				break ;
			}
			tmp_lst = tmp_lst->next;
		}
		if (!dir)
			dir = ft_strdup(home_arg);
	}
	else
	{
		dir = ft_calloc(sizeof(char), PATH_MAX);
		getcwd(dir, PATH_MAX - 1);
		dir = ft_ownrealloc(&ft_strjoin, &dir, "/");
	}
	rez = check_dir(envlst, add_dir, dir);
	free(dir);
	return (rez);
	
}

void
	ft_cd(char **line, t_list **envlst, char *home_add)
{
	if (!line[1])
		home_arg(envlst);
	else if (!ft_strncmp(line[1], ".", 2))
		return;
	else if (!ft_strncmp(line[1], "..", 3))
		two_dot(envlst);
	else if (!ft_strncmp(line[1], "-", 2))
		divis(envlst);
	else if (!ft_strncmp(line[1], "--", 3) || !ft_strncmp(line[1], "~", 2))
		home_arg(envlst);
	else
		add_dir(envlst, line[1], home_add);
}
