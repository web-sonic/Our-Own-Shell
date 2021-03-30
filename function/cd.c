/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:36 by sgath             #+#    #+#             */
/*   Updated: 2021/03/30 12:39:38 by sgath            ###   ########.fr       */
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
		if(!ft_strncmp(enviroment->value, "HOME", 5))
		{
			if (chdir(enviroment->argum < 0))
			{
				ft_putstr_fd("minishell: cd: ", 1);
				ft_putstr_fd(enviroment->argum, 1);
				ft_putstr_fd(": No such file or directory", 1);
			}
			return (1);
		}
	}
	ft_putendl_fd("minishell> cd: HOME not set", 1);
	return (1);
}

static int
	two_dot(t_list **envlst)
{
	t_list	*pwd_lst;
	t_list	*pwdold_lst;
	t_env	*enviroment;
	char	*dir;
	char	*tmp;
	int		len;

	dir = ft_calloc(sizeof(char), PATH_MAX);
	getcwd(dir, PATH_MAX - 1);
	len = ft_strlen(dir);
	len--;
	tmp = ft_strdup(dir);
	while(dir[--len] != '/')
		dir[len] = '\0';
	if (chdir(enviroment->argum < 0))
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(enviroment->argum, 1);
		ft_putstr_fd(": No such file or directory", 1);
	}
	else
	{
		pwd_lst = *envlst;
		pwdold_lst = *envlst;
		while (pwd_lst)
		{
			enviroment = pwd_lst->content;
			if(!ft_strncmp(enviroment->value, "PWD", 4))
			{
				dub_and_free(enviroment->argum, dir);
			}
			pwd_lst = pwd_lst->next;
		}
		while (pwdold_lst)
		{
			enviroment = pwd_lst->content;
			if(!ft_strncmp(enviroment->value, "OLDPWD", 4))
			{
				dub_and_free(enviroment->argum, tmp);
			}
			pwd_lst = pwd_lst->next;
		}
		
	}
	free(tmp);
	free(dir);
	return;
}

void
	ft_cd(char **line, t_list **envlst)
{
	int		rez;

	rez = 0;
	if (!line[0])
		rez = no_arg(envlst);
	if (rez == 0 && !ft_strncmp(line[1], ".", 2))
		return;
	if ( rez == 0 && !ft_strncmp(line[1], "..", 3))
		rez = two_dot(envlst);
}
