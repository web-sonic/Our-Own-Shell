/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:15:08 by sgath             #+#    #+#             */
/*   Updated: 2021/04/01 17:21:53 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char
	*find_in_lst(t_list *envlst, char *name)
{
	t_env	*enviroment;

	while (envlst)
	{
		enviroment = envlst->content;
		if(!ft_strncmp(enviroment->value, name, ft_strlen(name) + 1))
			return (enviroment->argum);
		envlst = envlst->next;	
	}
	return (NULL);
}
static int
	check_dir(t_list *envlst, char *dir_add)
{
	t_list	*pwd_lst;
	t_env	*enviroment;
	char	*dir_pwd;
	
	if (chdir(dir_add) == -1)
		return (1);
	pwd_lst = envlst;
	dir_pwd = ft_calloc(sizeof(char), PATH_MAX);
	getcwd(dir_pwd, PATH_MAX - 1);
	while (pwd_lst)
	{
		enviroment = pwd_lst->content;
		if(!ft_strncmp(enviroment->value, "PWD", 4))
			dub_and_free(&(enviroment->argum), dir_add);
		if(!ft_strncmp(enviroment->value, "OLDPWD", 7))
		{
			dub_and_free(&(enviroment->argum), dir_pwd);
			enviroment->equally = 1;
		}
		pwd_lst = pwd_lst->next;
	}
	free (pwd_lst);
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
	return (check_dir(envlst, dir_add));
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
	rez = check_dir(envlst, dir_pwd);
	free (dir_pwd);
	return (rez);
}

int
	ft_cd(char **line, t_list *envlst)
{
	int		rez;
	char	*tmp;

	rez = -1;
	if (!line[1])
		return(ret_dir(envlst, "HOME"));
	if (rez == -1 && !ft_strncmp(line[1], "-", 2))
		rez = ret_dir(envlst, "OLDPWD");
	if (rez == -1 && !ft_strncmp(line[1], "--", 3))
		rez = ret_dir(envlst, "HOME");
	tmp = line[1];
	if (rez == -1 && line[1][0] == '~' && (line[1][1] == '\0' || line[1][1] == '/'))
	{
		rez = ret_dir(envlst,"HOME");
		if (line[1][1] == '/')
			rez = -1;
		tmp += 2;
	}
	if (rez == -1)
		rez = full_dir(envlst, tmp);
	if (rez == 1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(line[1], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	return (rez);
}