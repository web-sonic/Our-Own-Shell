/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:47:07 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/16 13:53:27 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define STATUS 1;
/* 
** @params: int argc: 
**			int argv:
** Имитирует работу шелла
** @return char *line: введенная строка в терминале
*/
void
	shell_loop(int argc, char **argv)
{
	char *line;
	t_list table;

	while (STATUS)
	{
		line = readline();
//		table = parser(table);
//		execute(table);
	}

}