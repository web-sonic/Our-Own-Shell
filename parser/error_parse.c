/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:43:16 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/25 11:11:00 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* 
** @params: char *str обрабатываемая строка
**			t_list processes список команд в баше
** TODO добавляет новый список команд в список 
** @return: int корректность выполнения команды
*/
int
	error_parse(char *str, int c)
{
	ft_putstr_fd("minishell: ", 2);
	if (c)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" `", 2);
		ft_putchar_fd(c, 2);
		ft_putendl_fd("'", 2);
	}
	else
		ft_putendl_fd(str, 2);
	return (0);
}