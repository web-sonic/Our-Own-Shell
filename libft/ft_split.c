/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 16:38:41 by ctragula          #+#    #+#             */
/*   Updated: 2021/01/17 22:21:34 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_is_word(char *s, char c)
{
	while (*s == c && *s != '\0')
		s++;
	return (s);
}

static size_t	ft_lenword(char *s, char c)
{
	size_t	len;
	char	*str;

	str = s;
	len = 0;
	while (*str != c && *str++ != '\0')
		len++;
	return (len);
}

static size_t	ft_count_word(char *s, char c)
{
	char	*str;
	size_t	count;
	size_t	len;

	count = 0;
	str = (char *)s;
	while (*str != '\0')
	{
		str = ft_is_word(str, c);
		if (*str != '\0')
		{
			count++;
			len = ft_lenword(str, c);
			str += len;
		}
	}
	return (count);
}

char			**ft_split(char const *s, char c)
{
	size_t	count;
	char	**arr;
	char	*str;
	size_t	len;

	if (!s)
		return (NULL);
	str = ((char *)s);
	count = ft_count_word(str, c);
	if (!(arr = ft_calloc(count + 1, sizeof(char *))))
		return (NULL);
	len = 0;
	while (*str != '\0' && len < count)
	{
		str = ft_is_word(str, c);
		if (str && !(arr[len] = ft_substr(str, 0, ft_lenword(str, c))))
		{
			ft_wordtab_clear(arr);
			return (NULL);
		}
		len++;
		str += ft_lenword(str, c);
	}
	return (arr);
}
