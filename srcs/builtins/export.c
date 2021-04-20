/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:58 by sgath             #+#    #+#             */
/*   Updated: 2021/04/20 09:34:47 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	t_list	*tmp_lst;

	sort_lst = ft_lstmap(tmp_lstenv, &return_content, free_env);
	ft_lstsort(&sort_lst, &cmp_sort);
	tmp_lst = sort_lst;
	while (tmp_lst)
	{
		envt = tmp_lst->content;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(envt->val, 1);
		if (envt->equally == 1)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(envt->arg, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		tmp_lst = tmp_lst->next;
	}
	ft_lstclear(&sort_lst, &free_env);
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
	free_env(arr_arg);
	return (1);
}

static void
	add_line(char *line, t_list **envlst, int plus)
{
	int		add;
	t_env	*envt;
	t_env	*arr_arg;
	t_list	*tmp_lst;

	arr_arg = malloc(sizeof(t_env));
	line_split(arr_arg, line, plus);
	add = 0;
	tmp_lst = *envlst;
	while (tmp_lst && add == 0)
	{
		envt = tmp_lst->content;
		if (!ft_strncmp(arr_arg->val, envt->val, ft_strlen(arr_arg->val) + 1))
			add = add_arg(arr_arg, &envt, plus);
		tmp_lst = tmp_lst->next;
	}
	if (add == 0)
		ft_lstadd_back(envlst, ft_lstnew(arr_arg));
}

int
	ft_export(char **line, t_list *envlst, int pipe)
{
	t_exp	exp;

	exp.i = 0;
	exp.rez = 0;
	if (!line[1])
		return (print_env(envlst));
	if (!envlst)
		return (0);
	while (line[++(exp.i)] && exp.rez != 2)
	{
		exp.plus = 0;
		exp.error = 0;
		if (ft_isdigit(line[exp.i][0]) || line[exp.i][0] == '=' ||
			(line[exp.i][0] == '-' && line[exp.i][1] == '\0'))
			exp.error = valid_error(line[0], line[exp.i]);
		if (exp.error == 0 && line[1][0] == '-' && line[1][1])
			exp.error = flag_error(line[0], line[1]);
		check_line_export(line[exp.i], &exp);
		if (exp.error == 0 && pipe == 1)
			add_line(line[exp.i], &envlst, exp.plus);
		exp.rez = exp.error;
	}
	return (exp.rez);
}
