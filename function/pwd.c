#include "../minishell.h"

int
	ft_pwd(void)
{
	char *dir;

	dir = ft_calloc(sizeof(char), PATH_MAX);
	if (!dir)
		return(1);
	if (!getcwd(dir, PATH_MAX - 1))
		return (1);
	ft_putendl_fd(dir, 1);
	free(dir);
	return (0);
}