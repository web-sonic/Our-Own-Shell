/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:47:22 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/25 21:25:51 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*find_way(void)
{
	char	*dir;
	char	*str;
	char	**way;
	int		i;

	i = -1;
	way = 0;
	str = ft_strdup("/tmp/histlist");
	dir = ft_calloc(sizeof(char), PATH_MAX);
	if (getcwd(dir, PATH_MAX - 1))
	{
		way = ft_split(dir, '/');
		if (way[1] && !ft_strncmp(way[0], "Users", 6))
		{
			free(str);
			str = ft_strjoin("/Users/", way[1]);
			str = ft_ownrealloc(&ft_strjoin, &str, "/histlist");
		}
	}
	ft_wordtab_clear(way);
	free(dir);
	return (str);
}

void
	inint_histlist(t_dlist **histlist, char *dir_add)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(dir_add, O_RDONLY | O_CREAT, 0777);
	if (fd < 0)
	{
		perror("-");
		exit(2);
	}
	while ((i = get_next_line(fd, &line)) > 0)
		ft_dlstadd_back(histlist, ft_dlstnew(line));
	if (i == -1)
		exit(2);
	close(fd);
}

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
	char	*dir_add;
	t_list	*cmd_lst;
	t_list	*pipe_lst;
	char	*str;

	dir_add = find_way();
	inint_histlist(&histlist, dir_add);
	argv[0] += 2;
	while (argc)
	{
		ft_putstr_fd(argv[0], 1);
		ft_putstr_fd("> ", 1);
		line = readline(&histlist, dir_add);
		if (line)
		{
			cmd_lst = get_cmds(line);
	//		if (cmd_lst)
	//			execute(cmd_lst, env);
		}
	}
	return (0);
}


//если курсор близко к краю терминала - не работает
// изменение окна терминала починить
// очистка терминала работает?
// дописать функции + функция history
// парсер
// дюпы, пайпы, исполнение команд
// написать свою функцию getenv
// проверка существования файла
//исправить 777 в создании файла