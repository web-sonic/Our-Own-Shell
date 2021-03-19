/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 16:03:34 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/19 15:50:18 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.c"

/*
** @params: t_list *lst указатель на список
** TODO возвращает content последнего элемента списка
** @return: void* указатель на list->content
*/
void
	*get_lastlst_data(t_list *lst)
{
	t_list	*last_lst;

	last_lst = ft_lstlast(lst);
	return (last_lst->content);
}

/*
** @params: t_com command структура команды
** TODO инициализация структуры команды
** @return: NULL
*/
void
	init_command(t_com *command)
{
	command->args = 0;
	command->fdin = 0;
	command->fdout = 0;
}

/* 
** @params: char *str обрабатываемая строка
**			t_list processes список команд в баше
** TODO добавляет новый список команд в список 
** @return: int корректность выполнения команды
*/
int
	add_command(char **str, t_list *processes)
{
	t_list	*process;
	t_com	command;

	if (str)
	{
		(*str)++;
		ft_strtrim(*str, " \t");
		if (**str == '\0')
			return (error_parse(PIPE_UNDEF));
	}
	process = ft_lstlast(processes);
	init_command(&command);
	ft_lstadd_back(process, ft_lstnew(&command));
}

/* 
** @params: char *str обрабатываемая строка
**			t_list processes список команд в баше
** TODO создает и добавляет в список новый элемент,
**	содержащий новый список команд
** @return: int корректность выполнения команды
*/
void
	add_process(char **str, t_list *processes)
{
	t_list	*process;
	ft_lstadd_back(processes, ft_lstnew(process));
	if (str)
		(*str)++;
}

/* 
** @params: char *str обрабатываемая строка
**			t_list processes список команд в баше
** TODO добавляет аргумент в команду
** @return: int корректность выполнения команды
*/
void
	add_argument(char **str, t_list *processes)
{
	t_list	*com_list;
	t_list	*arglst;
	t_com	*command;
	char	*arg;

	com_list = ft_lastlst_data(processes);
	command = ft_lastlst_data(com_list);
	arg = parse_arg(str);
	arglst = command->args;
	ft_lstadd_back(arglst, ft_lstnew(arg));
}