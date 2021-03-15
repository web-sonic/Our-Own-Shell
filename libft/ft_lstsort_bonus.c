/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 20:29:27 by ctragula          #+#    #+#             */
/*   Updated: 2021/02/15 15:22:18 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort(t_list **begin_list, int (*cmp)())
{
	t_list	*i;
	t_list	*j;
	void	*temp_data;

	i = *begin_list;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if ((*cmp)(i->content, j->content) > 0)
			{
				temp_data = i->content;
				i->content = j->content;
				j->content = temp_data;
			}
			j = j->next;
		}
		i = i->next;
	}
}
