/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordtab_realloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:42:41 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/05 12:45:39 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char
	**ft_wordtab_realloc(char **wordtab, char *str)
{
	char	**tmp_tab;
	int		i;

	tmp_tab = wordtab;
	wordtab = malloc(sizeof(char *) * (ft_wordtab_count(tmp_tab) + 2));
	i = 0;
	while (tmp_tab[i])
	{
		wordtab[i] = ft_strdup(tmp_tab[i]);
		i++;
	}
	wordtab[i] = ft_strdup(str);
	wordtab[i + 1] = 0;
	ft_wordtab_clear(tmp_tab);
	return (wordtab);
}
