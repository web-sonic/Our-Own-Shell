#include "../minishell.h"

void
	ft_env(char **env)
{
	int i;

	i = -1;
	while (env[++i])
		ft_putendl_fd(env[i], 1);
}
