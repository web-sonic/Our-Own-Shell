/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:31:09 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/04 15:32:46 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct		s_cmd
{
	t_bool			is_fdin;
	t_bool			is_fdout;
	int				add_fd;
	int				fdin;
	int				fdout;
	char			**args;
}					t_cmd;

typedef struct		s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}					t_dlist;

typedef struct		s_str
{
	char			*line_term;
	char			*rem_str;
	char			*tmp_str;
}					t_str;

typedef struct		s_env
{
	char			*val;
	char			*arg;
	int				equally;
}					t_env;

typedef struct		s_token
{
	char			*str;
	int				type;
}					t_token;

typedef struct		s_fdstruct
{
	int				tmpin;
	int				tmpout;
	int				fdin;
	int				fdout;
}					t_fdstruct;

typedef struct		s_exp
{
	int				i;
	int				rez;
	int				error;
	int				plus;
}					t_exp;


#endif
