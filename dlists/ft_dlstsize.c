/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 10:47:36 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/21 13:48:10 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_dlstsize(t_dlist *lst)
{
	int	i;
	t_dlist *lst2;
	
	i = 0;
	lst2 = lst;
	if (lst)
	{
		i++;
		while (lst->next != 0)
		{
			lst = lst->next;
			i++;
		}
		while (lst2->prev != 0)
		{
			lst2 = lst2->prev;
			i++;
		}
	}
	return (i);
}
