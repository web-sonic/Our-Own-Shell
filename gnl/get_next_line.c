/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 14:25:31 by ctragula          #+#    #+#             */
/*   Updated: 2021/01/15 21:59:47 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char		*tmp;
	char			*buf;
	char			*swp;
	int				ret;

	if (BUFFER_SIZE < 1)
		return (-1);
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE))))
		return (ft_gnl_error(&tmp, NULL, NULL));
	while (!ft_nl(tmp) && (ret = read(fd, buf, BUFFER_SIZE)))
	{
		if (ret < 0 || (ret == 0 && !tmp))
			return (ft_gnl_error(&buf, &tmp, NULL));
		if (!(swp = ft_superjoin(tmp, buf, ret)))
			return (ft_gnl_error(&buf, &tmp, NULL));
		free(tmp);
		if (!(tmp = ft_superjoin(swp, NULL, 0)))
			return (ft_gnl_error(&swp, &tmp, &buf));
		free(swp);
	}
	free(buf);
	return (ft_return_line(line, &tmp, swp, ret));
}
