/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export .c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:58 by sgath             #+#    #+#             */
/*   Updated: 2021/03/28 18:35:41 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int
	cmp_sort(t_env *cont, t_env *next)
{
	return(ft_strncmp(cont->value, next->value, ft_strlen(cont->value) + 1));
}

void
	print_env(t_list *tmp_lstenv)
{
	t_env	*enviroment;

	ft_lstsort(&tmp_lstenv, &ft_strncmp);
	while (tmp_lstenv)
	{
		enviroment = tmp_lstenv->content;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(enviroment->value, 1);
		if(enviroment->equally == 1)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(enviroment->argum, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		tmp_lstenv = tmp_lstenv->next;
	}
}

void
	add_line(char *line, t_list **envlst)
{
	int add;
	t_list	*tmp_lstenv;
	t_env	*enviroment;
	t_env	*arr_arg;

	line_split(&arr_arg, line);
	tmp_lstenv = *envlst;
	add = 0;
	arr_arg = malloc(sizeof(t_env));
	while (tmp_lstenv && add == 0)
	{
		enviroment = tmp_lstenv->content;
		if (!ft_strncmp(arr_arg->value, enviroment->value, ft_strlen(arr_arg->value) + 1))
			if (arr_arg->argum)
				add = dub_and_free(enviroment->argum, arr_arg->argum);
		tmp_lstenv = tmp_lstenv->next;
	}
	if (add == 0)
	{
		tmp_lstenv = *envlst;
		ft_dlstadd_back(&tmp_lstenv, &arr_arg);
	}
}

int
	print_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 1);
	ft_putstr_fd(str, 1);
	ft_putnbr_fd("': not a valid identifier", 1);
	return (1);
}

void
	ft_export(char **line, t_list **envlst)
{
	int		i;
	int		j;
	int		error;
	t_list	*tmp_lstenv;

	i = -1;
	error = 0;
	tmp_lstenv = *envlst;
	if(!line[0])
	{
		print_env(tmp_lstenv);
		return;
	}
	while (line[++i])
	{
		j = -1;
		while (line[i][++j])
			if (line[i][j] != '_' && !ft_isalnum(line[i][j]) && !ft_isalpha(line[i][0]))
				error = print_error(line[i]);
		if (error != 1)
			add_line(line[i], envlst);
	}
}
