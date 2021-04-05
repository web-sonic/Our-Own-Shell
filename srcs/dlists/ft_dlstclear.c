/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:29:49 by sgath             #+#    #+#             */
/*   Updated: 2021/04/05 12:45:03 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void
	ft_dlstdelone(t_dlist *lst, void (*del)(void*))
{
	if (lst)
	{
		(*del)(lst->content);
		free(lst);
	}
}

void
	ft_dlstclear(t_dlist **lst, void (*del)(void*))
{
	t_dlist	*tmp;
	t_dlist	*list;

	list = *lst;
	*lst = NULL;
	while (list)
	{
		tmp = list->next;
		ft_dlstdelone(list, (*del));
		list = tmp;
	}
}
