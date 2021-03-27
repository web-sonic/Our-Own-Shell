/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export .c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:08:58 by sgath             #+#    #+#             */
/*   Updated: 2021/03/27 16:28:37 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void
	print_env()
{
	t_env	*enviroment;
	t_list	*tmp_lstenv;

	tmp_lstenv = g_lstenv;
	ft_lstsort(&tmp_lstenv, );
	enviroment = g_lstenv->content;
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(enviroment->value, 1);
	if(enviroment->value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(enviroment->argum, 1);
		ft_putchar_fd('"', 1);
	}
	ft_putchar_fd('\n', 1);
}

void
	ft_export(char **line)
{
	int i;

	i = -1;
	if(!line[0])
		print_env();
	
}
