/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordtab_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 14:41:15 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/16 17:38:03 by sgath            ###   ########.fr       */
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
