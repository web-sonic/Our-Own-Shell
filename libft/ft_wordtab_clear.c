/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordtab_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 14:40:23 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/16 21:05:15 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_wordtab_clear(char **tab_lst)
{
	int	count;

	count = 0;
	while (tab_lst[count])
	{
		free(tab_lst[count]);
		count++;
	}
	free(tab_lst[count]);
	free(tab_lst);
}
