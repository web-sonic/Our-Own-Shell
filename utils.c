/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 17:15:21 by sgath             #+#    #+#             */
/*   Updated: 2021/03/21 12:03:27 by ctragula         ###   ########.fr       */
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
	return (dst);
}

char
	*ft_strownjoin(char *dst, char *src)
{
	char	*tmp_str;

	tmp_str = ft_strjoin(dst, src);
	free(dst);
	return (tmp_str);
}
