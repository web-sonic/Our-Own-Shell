/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:47:22 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/21 12:32:17 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
** @params: char **env: массив переменных окружения
**			char *name: название minishell
** TODO: shell_loop: Имитирует работу шелла
** @return NULL
*/
void
	shell_loop(char *name, char **env, t_dlist **histlist)
{
	char	*line;
	t_list	*table;

	name += 2;
	ft_putstr_fd(name, 1);
	ft_putstr_fd("> ", 1);
	line = readline(env, histlist);
	table = ft_parser(line);
//	execute(table);
}

int
	main(int argc, char **argv, char **env)
{
	t_dlist	*histlist;

	while (argc)
		shell_loop(argv[0], env, &histlist);
	return (0);
}