/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 06:18:41 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/04 20:13:36 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLIST_H
# define DLIST_H

# include "../minishell.h"

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);
t_dlist	*ft_dlstnew(void *content);
int		ft_dlstsize(t_dlist *lst);
void	ft_dlstclear(t_dlist **lst, void (*del)(void*));

#endif
