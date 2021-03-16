/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:47:07 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/16 17:10:48 by ctragula         ###   ########.fr       */
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