/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:58 by sgath             #+#    #+#             */
/*   Updated: 2021/04/04 15:09:57 by sgath            ###   ########.fr       */
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

static int
	add_arg(t_env *arr_arg, t_env **envt, int plus)
{
	if (arr_arg->arg)
	{
		if (plus == 0)
			dub_and_free(&((*envt)->arg), arr_arg->arg);
		else
		{
			(!(*envt)->arg) ? (*envt)->arg = ft_strdup(arr_arg->arg) :
			((*envt)->arg = ft_ownrealloc(&ft_strjoin, &((*envt)->arg),
			arr_arg->arg));
		}
		(*envt)->equally = 1;
	}
	return (1);
}

static void
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
			add = add_arg(arr_arg, &envt, plus);
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
	t_exp	exp;

	exp.i = 0;
	exp.rez = 0;
	if (pipe == 0)
		return (0);
	if (!line[1])
		return (print_env(envlst));
	while (line[++(exp.i)] && exp.rez != 2)
	{
		exp.plus = 0;
		exp.error = 0;
		exp.j = -1;
		if (ft_isdigit(line[exp.i][0]) || line[exp.i][0] == '=')
			exp.error = export_error(line[exp.i]);
		if (exp.error == 0 && line[1][0] == '-' && line[1][1])
			exp.error = flag_error(line[0], line[1]);
		while (line[exp.i][++(exp.j)] &&
			line[exp.i][exp.j] != '=' && exp.error == 0)
			if (!(line[exp.i][exp.j] == '_' || ft_isalnum(line[exp.i][exp.j])))
			{
				if (line[exp.i][exp.j] == '+' && line[exp.i][exp.j + 1] == '=')
					exp.plus = 1;
				else
					exp.error = export_error(line[exp.i]);
			}
		if (exp.error == 0 && exp.rez != 2)
			add_line(line[exp.i], envlst, exp.plus);
		exp.rez = exp.error;
	}
	return (exp.rez);
}
