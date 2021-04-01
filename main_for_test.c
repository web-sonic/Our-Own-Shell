/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_for_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 13:47:22 by ctragula          #+#    #+#             */
/*   Updated: 2021/04/01 22:36:32 by yu               ###   ########.fr       */
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
	
	fd = open(dir_add, O_RDONLY | O_CREAT, 0755);
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
	int		lvl;
	t_env	*enviroment;

	i = -1;
	while (env[++i])
	{
		enviroment = malloc(sizeof(t_env));
		line_split(enviroment, env[i]);
		if (!ft_strncmp("SHLVL", enviroment->value, 6))
		{
			lvl = ft_atoi(enviroment->argum);
			enviroment->argum = ft_itoa(lvl + 1);
		}
		ft_lstadd_back(envlst, ft_lstnew(enviroment));
	}
	enviroment = malloc(sizeof(t_env));
	enviroment->argum = NULL;
	enviroment->value = ft_strdup("OLDPWD");
	enviroment->equally = 0;
	ft_lstadd_back(envlst, ft_lstnew(enviroment));
}

int
	empty_line(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && ft_strchr(SPACES, line[i]))
		i++;
	if (!line[i])
	{
		g_error = 0;
		return (1);
	}
	return (0);
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

	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, &signal_handler);
	histlist = 0;
	envlst = 0;
	dir_add = find_way();
	init_histlist(&histlist, dir_add);
	init_envlist(&envlst, env);
	int fd = open("tests/file_tests/error_tests.txt", O_RDONLY);
	argv[0] += 2;
	int i = 0;
	while (get_next_line(fd, &line) > 0)
	{
	 	ft_putnbr_fd(i++, 1);
		if (line && !empty_line(line))
		{
			if (line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = 0;
			cmd_lst = get_cmds(line);
			if (cmd_lst)
				execute(cmd_lst, envlst, mod_address(dir_add));
			free(line);
		}
	}
	ft_dlstclear(&histlist, free);
	return (0);
}

//если курсор близко к краю терминала - не работает
// изменение окна терминала починить
// история как в баше (звездочки, изменения строк и т.д. и т.п.)