/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:58 by sgath             #+#    #+#             */
/*   Updated: 2021/04/03 18:58:22 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int
	cmp_sort(t_env *cont, t_env *next)
{
	return (ft_strncmp(cont->val, next->val, ft_strlen(cont->val) + 1));
}

static int
	print_env(t_list *tmp_lstenv)
{
	t_env	*envt;
	t_list	*sort_lst;

	sort_lst = ft_lstmap(tmp_lstenv, &return_content, free_env);
	ft_lstsort(&sort_lst, &cmp_sort);
	while (sort_lst)
	{
		envt = sort_lst->content;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(envt->val, 1);
		if (envt->equally == 1)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(envt->arg, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		sort_lst = sort_lst->next;
	}
	return (0);
}

void
	add_line(char *line, t_list *envlst, int plus)
{
	int		add;
	t_list	*tmp_lstenv;
	t_env	*envt;
	t_env	*arr_arg;

	arr_arg = malloc(sizeof(t_env));
	line_split(arr_arg, line, plus);
	tmp_lstenv = envlst;
	add = 0;
	while (tmp_lstenv && add == 0)
	{
		envt = tmp_lstenv->content;
		if (!ft_strncmp(arr_arg->val, envt->val, ft_strlen(arr_arg->val) + 1))
		{
			if (arr_arg->arg)
			{
				if (plus == 0)
					dub_and_free(&(envt->arg), arr_arg->arg);
				else
					envt->arg = ft_ownrealloc(&ft_strjoin, &(envt->arg), arr_arg->arg);
				envt->equally = 1;
			}
			add = 1;
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
	ft_export(char **line, t_list *envlst, int pipe)
{
	int		i;
	int		j;
	int		rez;
	int		error;
	int		plus;

	i = 0;
	rez = 0;
	if (!line[1])
		return (print_env(envlst));
	if (pipe == 0)
		return (0);
	while (line[++i] && rez != 2)
	{
		plus = 0;
		error = 0;
		j = -1;
		if (ft_isdigit(line[i][0]) || line[i][0] == '=')
		{
			error = export_error(line[i]);
			rez = error;
		}
		if (error == 0 && line[1][0] == '-' && line[1][1])
		{
			error = flag_error(line[0], line[1]);
			rez = error;
		}
		while (error != 2 && line[i][++j] && line[i][j] != '=' && error == 0)
		{
			if (!(line[i][j] == '_' || ft_isalnum(line[i][j])))
			{
				if (line[i][j] == '+' && line[i][j + 1] == '=')
					plus = 1;
				else
				{
					error = export_error(line[i]);
					rez = error;
				}
			}
		}
		if (error == 0 && rez != 2)
			add_line(line[i], envlst, plus);
	}
	return (rez);
}
