/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:09:06 by sgath             #+#    #+#             */
/*   Updated: 2021/04/02 18:21:30 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void
	ft_unset(char **line, t_list **envlst, int pipe)
{
	t_env	*envt;
	t_list	*tmp_lstenv;
	t_list	*next_lstenv;
	int		i;

	if (!line[1] || pipe == 0)
		return ;
	envt = (*envlst)->content;
	i = 0;
	tmp_lstenv = *envlst;
	next_lstenv = (*envlst)->next;
	while (line[++i])
	{
		if (!ft_strncmp(line[i], envt->val, ft_strlen(envt->val) + 1))
		{
			tmp_lstenv->next = (*envlst)->next;
			ft_lstdelone((*envlst), &free_env);
			*envlst = tmp_lstenv;
		}
	}
	check_next_lst(tmp_lstenv, next_lstenv, line);
}
