/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:31:09 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/19 20:12:23 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct		s_com
{
	int				fdin;
	int				fdout;
	t_list			*args;
}					t_com;

typedef struct		s_dlist
{
	void			*content;
	t_dlist			*next;
	t_dlist			*prev;
}					t_dlist;

#endif