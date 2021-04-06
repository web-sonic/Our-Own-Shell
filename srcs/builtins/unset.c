/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:09:06 by sgath             #+#    #+#             */
/*   Updated: 2021/04/06 15:17:11 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void
	check_next_lst(t_list *lstenv, char **line)
{
	int		i;
	t_env	*envt;
	t_list	*prew;
	t_list	*next;

	i = 0;
	while (line[++i])
	{
		prew = lstenv;
		next = lstenv->next;
		while (next)
		{
			envt = next->content;
			if (!ft_strncmp(line[i], envt->val, ft_strlen(envt->val) + 1))
			{
				prew->next = next->next;
				ft_lstdelone(next, &free_env);
				next = 0;
				break ;
			}
			if (next)
				next = next->next;
			prew = prew->next;
		}
	}
}

static int
	check_line_uns(char *line)
{
	int i;
	int rez;

	i = -1;
	rez = 0;
	while (line[++i] && rez == 0)
	{
		if (line[i] != '_' && !ft_isalnum(line[i]))
			rez = 1;
	}
	return (rez);
}

static int
	check_first_lst(t_list *tmp_lstenv, t_list *next_lstenv, char **line)
{
	int		i;
	int		rez;
	t_env	*envt;

	i = 0;
	rez = 0;
	envt = tmp_lstenv->content;
	while (line[++i] && rez != 2)
	{

		if (ft_isdigit(line[i][0]) || line[i][0] == '=' || (line[i][0] == '-'
			&& line[i][1] == '\0') || check_line_uns(line[i]) != 0)
			rez = valid_error(line[0], line[i]);
		if (line[i][0] == '-' && line[i][1] != '\0')
			rez = flag_error(line[0], line[1]);
		if (!ft_strncmp(line[i], envt->val, ft_strlen(envt->val) + 1))
		{
			ft_lstdelone(tmp_lstenv, &free_env);
			tmp_lstenv = next_lstenv;
			break ;
		}
	}

	return (rez);
}

int
	ft_unset(char **line, t_list **envlst, int pipe)
{
	if (!line[1] || pipe == 0)
		return (0);
	if (!(*envlst))
		return (0);
	if (check_first_lst(*envlst, (*envlst)->next, line) != 0)
		return (1);
	check_next_lst(*envlst, line);
	return (0);
}
