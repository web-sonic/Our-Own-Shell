/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:47:22 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/25 13:49:55 by ctragula         ###   ########.fr       */
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
	t_list	*cmd_lst;
	t_list	*pipe_lst;
	char	*str;

	argv[0] += 2;
	while (argc)
	{
		ft_putstr_fd(argv[0], 1);
		ft_putstr_fd("> ", 1);
		line = readline(&histlist);
		if (line)
		{
			cmd_lst = get_cmds(line);
			if (cmd_lst)
				execute(cmd_lst, env);
		}
	}
	return (0);
}


//если курсор близко к краю терминала - не работает
//добавить найм в рид
//