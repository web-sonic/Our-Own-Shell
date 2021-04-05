/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:15:21 by sgath             #+#    #+#             */
/*   Updated: 2021/04/05 12:48:54 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int
	super_strlen(int start, char symbol, char *str)
{
	int	len;

	len = 0;
	while (str[start] != symbol && str[start++])
		len++;
	return (len);
}

char
	*mod_address(char *dir_add)
{
	char	*new_dir;
	char	*str;

	new_dir = ft_strdup(dir_add);
	str = ft_strrchr(new_dir, '/');
	if (str)
		*str = 0;
	return (new_dir);
}
