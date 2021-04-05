/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:09:06 by sgath             #+#    #+#             */
/*   Updated: 2021/04/05 12:47:39 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void
	check_next_lst(t_list *tmp_lstenv, t_list *next_lstenv, char **line)
{
	int		i;
	t_env	*envt;

	while (next_lstenv)
	{
		i = 0;
		envt = next_lstenv->content;
		while (line[++i])
		{
			if (!ft_strncmp(line[i], envt->val, ft_strlen(envt->val) + 1))
			{
				tmp_lstenv->next = next_lstenv->next;
				ft_lstdelone(next_lstenv, &free_env);
				next_lstenv = tmp_lstenv->next;
			}
		}
		tmp_lstenv = tmp_lstenv->next;
		if (next_lstenv)
			next_lstenv = next_lstenv->next;
	}
}

static int
	check_first_lst(t_list *tmp_lstenv, t_list *next_lstenv, char **line,
	int *rez)
{
	int		i;
	t_env	*envt;

	i = 0;
	envt = tmp_lstenv->content;
	while (line[++i])
	{
		if (!ft_strncmp(line[i], envt->val, ft_strlen(envt->val) + 1))
		{
			next_lstenv = tmp_lstenv->next;
			ft_lstdelone(tmp_lstenv, &free_env);
			tmp_lstenv = next_lstenv;
		}
		if (line[i][0] == '-' && line[i][1] == '\0')
		{
			ft_putendl_fd("minishell: unset: `-': not a valid identifier", 2);
			*rez = 1;
		}
		if (line[i][0] == '-' && line[i][1] != '\0')
			return (flag_error(line[0], line[1]));
	}
	return (0);
}

int
	ft_unset(char **line, t_list **envlst, int pipe)
{
	t_list	*tmp_lstenv;
	t_list	*next_lstenv;
	int		rez;

	rez = 0;
	if (!line[1] || pipe == 0)
		return (0);
	tmp_lstenv = *envlst;
	next_lstenv = (*envlst)->next;
	if (check_first_lst(tmp_lstenv, next_lstenv, line, &rez) != 0)
		return (1);
	check_next_lst(tmp_lstenv, next_lstenv, line);
	return (rez);
}
