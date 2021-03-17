/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:47:07 by ctragula          #+#    #+#             */
<<<<<<< HEAD:shell.c
/*   Updated: 2021/03/16 16:01:39 by sgath            ###   ########.fr       */
=======
/*   Updated: 2021/03/16 17:10:48 by ctragula         ###   ########.fr       */
>>>>>>> 9d4c4c5742e46078ff318e9707a00f4ce40e97aa:shell_loop.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



/* 
** @params: char **env: массив переменных окружения
**			char *name: название minishell
** Имитирует работу шелла
** @return NULL
*/
void
	shell_loop(char *name, char **env)
{
	char *line;
	t_list table;

	line = readline();
//	table = parser(line);fds
//	execute(table);
}