/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftplus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:44:13 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/04 06:48:27 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPLUS_H
# define LIBFTPLUS_H

#include "../minishell.h"
char	*ft_ownrealloc(char *(*f)(const char *, const char *),
			char **s1, char *s2);
char	**ft_wordtab_realloc(char **wordtab, char *str);
int		ft_putchar(int c);
int		dub_and_free(char **rem_str, char *str);
void	write_new_symbol_str(char **rem_str, char *str);
char	*ft_strtolower(char *str);

#endif
