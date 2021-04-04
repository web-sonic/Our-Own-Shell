/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_realloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:41:43 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/04 19:54:09 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void
	write_new_symbol_str(char **rem_str, char *str)
{
	char	*tmp;
	int		i;

	i = -1;
	while (str[++i])
		if (!ft_isprint(str[i]) && !ft_isonlyprint(str[i]) && str[i] != '\n')
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
