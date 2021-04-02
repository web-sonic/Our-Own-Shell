/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pact_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:33:17 by sgath             #+#    #+#             */
/*   Updated: 2021/04/02 18:33:32 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	dub_and_free(char **rem_str, char *str)
{
	if (*rem_str)
		free(*rem_str);
	*rem_str = ft_strdup(str);
	return (1);
}

void
	write_new_symbol_str(char **rem_str, char *str)
{
	char	*tmp;
	int		i;

	i = -1;
	while (str[++i])
		if (!ft_isprint(str[i]) && str[i] != '\n')
			return ;
	if (!(*rem_str))
		*rem_str = ft_strdup(str);
	else
	{
		tmp = ft_strjoin(*rem_str, str);
		free(*rem_str);
		*rem_str = tmp;
	}
}

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
