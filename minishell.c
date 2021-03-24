/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:47:22 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/24 11:05:47 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
** @params: char **env: массив переменных окружения
**			char *name: название minishell
** TODO: shell_loop: Имитирует работу шелла
** @return NULL
*/

int
	main(int argc, char **argv, char **env)
{
	t_dlist	*histlist;
	char	*line;
	char	*name;
	t_list	*cmd_lst;

	name = argv[0];
	(void)env;
	name += 2;
	while (argc)
	{
		ft_putstr_fd(name, 1);
		ft_putstr_fd("> ", 1);
		line = readline(&histlist);
		cmd_lst = get_cmds(line);
	//	execute(table);
	}
	return (0);
}