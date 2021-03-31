/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:58 by sgath             #+#    #+#             */
/*   Updated: 2021/03/31 13:17:23 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int
	cmp_sort(t_env *cont, t_env *next)
{
	return (ft_strncmp(cont->value, next->value, ft_strlen(cont->value) + 1));
}

static int
	print_env(t_list *tmp_lstenv)
{
	t_env	*enviroment;
	t_list	*sort_lst;

	sort_lst = ft_lstmap(tmp_lstenv, &return_content, free_env);
	ft_lstsort(&sort_lst, &cmp_sort);
	while (sort_lst)
	{
		enviroment = sort_lst->content;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(enviroment->value, 1);
		if(enviroment->equally == 1)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(enviroment->argum, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		sort_lst = sort_lst->next;
	}
	return (0);
}

void
	add_line(char *line, t_list *envlst)
{
	int		add;
	t_list	*tmp_lstenv;
	t_env	*enviroment;
	t_env	*arr_arg;

	arr_arg = malloc(sizeof(t_env));
	line_split(arr_arg, line);
	tmp_lstenv = envlst;
	add = 0;
	while (tmp_lstenv && add == 0)
	{
		enviroment = tmp_lstenv->content;
		if (!ft_strncmp(arr_arg->value, enviroment->value, ft_strlen(arr_arg->value) + 1))
		{
			if (arr_arg->argum)
				enviroment->equally = dub_and_free(&(enviroment->argum), arr_arg->argum);
			add = 1;
			break ;
		}
		tmp_lstenv = tmp_lstenv->next;
	}
	if (add == 0)
	{
		tmp_lstenv = envlst;
		ft_lstadd_back(&tmp_lstenv, ft_lstnew(arr_arg));
	}
}

int
	print_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 1);
	ft_putstr_fd(str, 1);
	ft_putendl_fd("': not a valid identifier", 1);
	return (1);
}

int
	ft_export(char **line, t_list *envlst)
{
	int		i;
	int		j;
	int		rez;
	int		error;
	t_list	*tmp_lstenv;

	i = 0;
	rez = 0;
	tmp_lstenv = envlst;
	if(!line[1])
		return (print_env(tmp_lstenv));
	while (line[++i])
	{
		error = 0;
		j = -1;
		while (line[i][++j])
			if (line[i][j] != '_' && !ft_isalnum(line[i][j]) && !ft_isalpha(line[i][0]))
			{
				error = print_error(line[i]);
				rez = error;
			}
		if (error != 1)
			add_line(line[i], envlst);
	}
	return (rez);
}
