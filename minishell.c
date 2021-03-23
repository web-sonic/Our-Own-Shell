/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:47:22 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/23 17:43:29 by sgath            ###   ########.fr       */
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
	t_list	*table;

	name = argv[0];
	(void)env;
	name += 2;
	while (argc)
	{
		ft_putstr_fd(name, 1);
		ft_putstr_fd("> ", 1);
		line = readline(&histlist);
		table = ft_parser(line);
	//	execute(table);
	}
	return (0);
}


//если курсор близко к краю терминала - не работает
//добавить найм в рид
//