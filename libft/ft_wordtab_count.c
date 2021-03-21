/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordtab_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 12:37:19 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/20 12:37:23 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wordtab_count(char **tab_lst)
{
	size_t	count;

	count = 0;
	while (*tab_lst++)
		count++;
	return (count);
}
