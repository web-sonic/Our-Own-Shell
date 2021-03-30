/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pact_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:15:21 by sgath             #+#    #+#             */
/*   Updated: 2021/03/30 20:20:31 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_putchar(int c)
{
	return (write(1, &c, 1));
}

char
	*ft_strldup(char *str, size_t len)
{
	char	*dst;

	dst = ft_calloc(len, sizeof(char));
	ft_strlcpy(dst, str, len);
	dst[len] = 0;
	return (dst);
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
	int len;

	len = 0;
	while (str[start] != symbol && str[start++])
		len++;
	return(len);
}

char
	*mod_address(char *dir_add)
{
	int	len;

	len = ft_strlen(dir_add);

	while(dir_add[--len] != '/')
		dir_add[len] = 0;
	return (dir_add);
}