/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctragula <ctragula@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:47:22 by ctragula          #+#    #+#             */
/*   Updated: 2021/03/26 22:43:10 by ctragula         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*g_lstenv;

static char
	*find_way(void)
{
	char	*dir;
	char	*str;
	char	**way;

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

static void
	evn_split(t_env *environment, char *env)
{
	int i;
	int j;

	i = -1;
	j = -1;
	environment->value = ft_calloc(sizeof(char), super_strlen(0, '=', env) + 1);
	if (!environment->value || !environment->argum)
		exit(1);
	while (env[++i] != '=')
		environment->value[i] = env[i];
	environment->argum = ft_calloc(sizeof(char), super_strlen(i, '\0', env) + 1);
	while (env[++i])
		environment->argum[++j] = env[i];
	// ft_putstr_fd(environment->value, 1);
	// ft_putchar_fd('=', 1);
	// ft_putendl_fd(environment->argum, 1);
}

static void
	init_list(t_dlist **histlist, char *dir_add, char **env)
{
	int		fd;
	int		i;
	char	*line;
	t_env	environment;

	
	fd = open(dir_add, O_RDONLY | O_CREAT, 0777);
	if (fd < 0)
	{
		perror("-");
		exit(1);
	}
	while ((i = get_next_line(fd, &line)) > 0)
		ft_dlstadd_back(histlist, ft_dlstnew(line));
	if (i == -1)
		exit(1);
	close(fd);
	i = -1;
	while (env[++i])
	{
		evn_split(&environment, env[i]);
		ft_lstadd_back(&g_lstenv, ft_lstnew(&environment));
		//ft_putendl_fd(g_lstenv->environment., 1);
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

	histlist = 0;
	dir_add = find_way();
	init_list(&histlist, dir_add, env);
	argv[0] += 2;
	while (argc)
	{
		ft_putstr_fd(argv[0], 1);
		ft_putstr_fd("> ", 1);
		line = readline(&histlist, dir_add);
		if (line)
		{
			cmd_lst = get_cmds(line);
			//if (cmd_lst)
			//	execute(cmd_lst, env);
		}
	}
	ft_dlstclear(&histlist, free);
	return (0);
}


//если курсор близко к краю терминала - не работает
// очистка терминала работает?
// дописать функции
// парсер
// дюпы, пайпы, исполнение команд
// написать свою функцию getenv
// проверка существования файла
//исправить 777 в создании файла
// изменение окна терминала починить
// история как в баше (звездочки, изменения строк и т.д. и т.п.)