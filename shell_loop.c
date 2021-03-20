/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:47:07 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/20 12:44:07 by ctragula         ###   ########.fr       */
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
	char	*line;
	t_list	*table;

	name += 2;
	ft_putstr_fd(name, 1);
	ft_putstr_fd("> ", 1);
	line = readline(env);
	table = ft_parser(line);
//	execute(table);
}