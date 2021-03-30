/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgath <sgath@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:47:22 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/30 16:54:20 by sgath            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	*find_way(void)
{
	char	*dir;
	char	*str;
	char	**way;

	way = 0;
	str = ft_strdup("/tmp/.minishell_history");
	dir = ft_calloc(sizeof(char), PATH_MAX);
	if (getcwd(dir, PATH_MAX - 1))
	{
		way = ft_split(dir, '/');
		if (way[1] && !ft_strncmp(way[0], "Users", 6))
		{
			free(str);
			str = ft_strjoin("/Users/", way[1]);
			str = ft_ownrealloc(&ft_strjoin, &str, "/.minishell_history");
		}
	}
	ft_wordtab_clear(way);
	free(dir);
	return (str);
}

static void
	init_histlist(t_dlist **histlist, char *dir_add)
{
	int		fd;
	int		i;
	char	*line;

	
	fd = open(dir_add, O_RDONLY | O_CREAT, 0777);
	if (fd < 0)
	{
		ft_putendl_fd(strerror(errno), 2);
		exit(1);
	}
	while ((i = get_next_line(fd, &line)) > 0)
		if(line[0] != '\0')
			ft_dlstadd_back(histlist, ft_dlstnew(line));
	if (i == -1)
		exit(1);
	close(fd);
}

void
	init_envlist(t_list **envlst, char **env)
{
	int		i;
	t_env	*environment;

	i = -1;

	while (env[++i])
	{
		environment = malloc(sizeof(t_env));
		line_split(environment, env[i]);
		ft_lstadd_back(envlst, ft_lstnew(environment));
	}
}

/* 
** @params: char **env: массив переменных окружения
** TODO: Имитирует работу шелла
** @return 0
*/
int
	main(int argc, char **argv, char **env)
{
	t_dlist	*histlist;
	char	*line;
	char	*dir_add;
	t_list	*cmd_lst;
	t_list	*envlst;

	histlist = 0;
	envlst = 0;
	dir_add = find_way();
	init_histlist(&histlist, dir_add);
	init_envlist(&envlst, env);
	argv[0] += 2;
	while (argc)
	{
		line = readline(&histlist, dir_add);
		if (line)
		{
			cmd_lst = get_cmds(line);
			if (cmd_lst)
				execute(cmd_lst, envlst);
		}
	}
	ft_dlstclear(&histlist, free);
	return (0);
}


//если курсор близко к краю терминала - не работает
// дописать функции
// парсер
// дюпы, пайпы, исполнение команд
// проверка существования файла
//исправить 777 в создании файла
// изменение окна терминала починить
// история как в баше (звездочки, изменения строк и т.д. и т.п.)
// нужна функция, которая превращает глобальный лист в список строк наподобии **env
// обработчик ошибок
// сигналы
