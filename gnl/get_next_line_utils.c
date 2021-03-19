/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:20:57 by ctragula          #+#    #+#             */
/*   Updated: 2021/01/15 22:00:11 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_nl(char *str)
{
	if (str)
		while (*str)
			if (*str++ == '\n')
				return (1);
	return (0);
}

int		ft_gnl_error(char **str1, char **str2, char **str3)
{
	if (str1)
		if (*str1)
			free(*str1);
	if (str2)
		if (*str2)
			free(*str2);
	if (str3)
		if (*str3)
			free(*str3);
	return (-1);
}

char	*ft_superjoin(char const *s1, char const *s2, size_t len)
{
	char	*s3;
	size_t	i;
	size_t	strlen;

	i = 0;
	strlen = 0;
	if (s1)
		while (s1[i++])
			strlen++;
	i = 0;
	if (!(s3 = malloc(sizeof(char) * (len + strlen + 1))))
		return (NULL);
	while (i < len + strlen + 1)
		s3[i++] = 0;
	i = 0;
	if (s1)
		while (*s1)
			s3[i++] = *s1++;
	if (s2)
		while (len--)
			s3[i++] = *s2++;
	return (s3);
}

int		ft_return_line(char **line, char **str, char *tmp, int len)
{
	if (!(*str) && !len)
	{
		if (!(*line = ft_superjoin(NULL, "", len)))
			return (ft_gnl_error(str, NULL, NULL));
		return (0);
	}
	len = 0;
	while ((*str)[len] && (*str)[len] != '\n')
		len++;
	if (!(*line = ft_superjoin(NULL, *str, len)))
		return (ft_gnl_error(str, NULL, NULL));
	if ((*str)[len] != '\n')
	{
		free(*str);
		*str = NULL;
		return (0);
	}
	if (!(tmp = ft_superjoin(*str + len + 1, NULL, 0)))
		return (ft_gnl_error(str, line, NULL));
	free(*str);
	if (!(*str = ft_superjoin(tmp, NULL, 0)))
		return (ft_gnl_error(&tmp, line, NULL));
	free(tmp);
	return (1);
}
