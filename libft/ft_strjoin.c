/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:18:18 by ctragula          #+#    #+#             */
/*   Updated: 2020/11/07 17:56:39 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	lens1;
	size_t	lens2;

	if (!s1 || !s2)
		return (NULL);
	lens1 = 0;
	lens2 = 0;
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	s3 = ft_calloc(sizeof(*s1), lens1 + lens2 + 1);
	if (s3)
	{
		ft_strlcpy(s3, s1, lens1 + 1);
		ft_strlcat(s3, s2, lens1 + lens2 + 1);
	}
	return (s3);
}
