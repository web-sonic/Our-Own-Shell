/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordtab_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 14:40:23 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/16 21:05:15 by yu               ###   ########.fr       */
=======
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 14:40:23 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/16 17:38:41 by sgath            ###   ########.fr       */
>>>>>>> ca124e6c1c2770c59c7994751126539232187474
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
