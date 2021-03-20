/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordtab_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 12:37:34 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/20 12:37:35 by ctragula         ###   ########.fr       */
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
