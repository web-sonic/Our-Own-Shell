/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelfirst_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 12:00:33 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/03 15:48:02 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	ft_lstdelfirst(t_list **lst, void (*del)(void*))
{
	t_list *tmp;

	tmp = (*lst)->next;
	ft_lstdelone(*lst, del);
	*lst = tmp;
}
