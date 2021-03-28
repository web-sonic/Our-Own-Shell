/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:36 by sgath             #+#    #+#             */
/*   Updated: 2021/03/28 18:51:28 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void
	ft_cd(char **line, t_list **envlst)
{
	t_list	*tmp_lst;
	t_env	*enviroment;

	tmp_lst = *envlst;
	if (!line[0])
	{
		while (tmp_lst)
		{
			if(!ft_strncmp(enviroment->value, "HOME", 5))
			{
				
				return;
			}
		}
		ft_putendl_fd("minishell> cd: HOME not set", 1);
		return;
	}
}