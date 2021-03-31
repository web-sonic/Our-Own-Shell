/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 17:15:08 by sgath             #+#    #+#             */
/*   Updated: 2021/03/31 18:12:25 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int
	home_dir(t_list *envlst)
{
	t_list	*tmp_lst;
	t_env	*enviroment;

	tmp_lst = envlst;
	while (tmp_lst)
	{
		enviroment = tmp_lst->content;
		if(!ft_strncmp(enviroment->value, "HOME", 5))
			return (check_dir(envlst,enviroment->argum, 0));
		tmp_lst = tmp_lst->next;
	}
	ft_putendl_fd("minishell: cd: HOME not set", 2);
	return (1);
}

int
	ret_dir(t_list *envlst)
{
	t_list	*tmp_lst;
	t_env	*enviroment;
	int rez;

	rez = 1;
	tmp_lst = envlst;
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

int
	ft_cd(char **line, t_list *envlst, char *home_add)
{
	int		rez;
	char	*tmp;
	char	**arr_dir;

	rez = -1;
	if (!line[0])
		return(home_dir(envlst));
	if (!ft_strncmp(line[1], "-", 2))
		return (ret_dit(envlst));
	if (!ft_strncmp(line[1], "--", 3))
		return (home_dir(envlst));
	tmp = line[1];
	if (line[1][0] == '~' && (line[1][1] == '\0' || line[1][1] == '/'))
	{
		rez = home_dir(envlst);
		if (rez == 1 || rez == 0 && line[1][1] == '\0')
			return (rez);
		tmp += 2;
	}
	arr_dir = ft_split(tmp, '/');
	
	
	return (0);
}