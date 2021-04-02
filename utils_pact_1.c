/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pact_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:15:21 by sgath             #+#    #+#             */
/*   Updated: 2021/04/02 18:25:05 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

char
	*ft_ownrealloc(char *(*f)(const char *, const char *), char **s1, char *s2)
{
	char	*tmp_str;

	tmp_str = f(*s1, s2);
	free(*s1);
	return (tmp_str);
}

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
