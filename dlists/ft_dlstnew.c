/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 09:27:02 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/19 20:11:12 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*tmp;

	if (!(tmp = malloc(sizeof(t_dlist))))
		return (NULL);
	tmp->content = content;
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}
