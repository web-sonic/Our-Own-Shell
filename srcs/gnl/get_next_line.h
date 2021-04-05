/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 16:28:05 by ctragula          #+#    #+#             */
/*   Updated: 2021/01/15 21:59:21 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);
int		ft_nl(char *str);
int		ft_gnl_error(char **str1, char **str2, char **str3);
int		ft_return_line(char **line, char **str, char *tmp, int len);
char	*ft_superjoin(char const *s1, char const *s2, size_t len);

#endif
