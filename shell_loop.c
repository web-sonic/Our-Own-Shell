/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:47:07 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/18 13:11:36 by sgath            ###   ########.fr       */
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
	shell_loop(char *name, char **env)
{
	char *line;
	t_list table;

	ft_putstr_fd(name, 1);
	ft_putchar_fd('>', 1);
	//printf("%s>", name);
	line = readline(env);
	if (!line)
		exit(1);
//	table = parser(line);
//	execute(table);
}