/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export .c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:58 by sgath             #+#    #+#             */
/*   Updated: 2021/03/27 18:41:57 by sgath            ###   ########.fr       */
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
		if(enviroment->value)
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
	ft_export(char **line, t_list **envlst)
{
	int i;
	t_list	*tmp_lstenv;
	t_list	*sort_lstenv;
	t_env	*enviroment;
	
	tmp_lstenv = *envlst;
	sort_lstenv = *envlst;
	i = -1;
	if(!line[0])
	{
		print_env(tmp_lstenv);
		return;
	}
	while (tmp_lstenv)
	{
		enviroment = tmp_lstenv->content;
		while (line[++i])
		{
			if (line[i][0] != '_' && !ft_isalpha(line[i][0]))
			{
				ft_putstr_fd("minishell: export: `", 1);
				ft_putstr_fd(line[i], 1);
				ft_putnbr_fd("': not a valid identifier", 1);
				break ;
			}
			if (!ft_strncmp(line[i], enviroment->value, ft_strlen(line[i]) + 1))
				dub_and_free(enviroment->argum, line[i]);
		}
	}
	
	
}
