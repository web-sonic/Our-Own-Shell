#include "minishell.h"
#include <string.h>

int
	main(int ac, char **av, char **env)
{
	char	*str;
	char	*temp_name;
	int		i;
	struct	termios term;

	temp_name = ft_strdup("xterm-256color");
	str = ft_calloc(sizeof(char), 2000);
	if (!temp_name || !str)
		return (1);
	if (tcgetattr(0, &term) < 0)
	{
		printf("%d\n", errno);
		return(1);
	}
	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~ICANON;
	if (tcsetattr(0, TCSANOW, &term) < 0)
	{
		printf("%d\n", errno);
		return(1);
	}
	tgetent(0, temp_name);
	//term.c_cc[VMIN] = 1;
	//term.c_cc[VTIME] = 0;
	//do
	while(strcmp(str, "\n"))
	{
		i = read(0, str, 100);
		if (ft_strcmp(str, "\e[A") == 0)
			write(1, "up\n", 3);
		else if (ft_strcmp(str, "\e[B") == 0)
			write(1, "down\n", 5);
		else if (ft_strcmp(str, "\e[C") == 0 || ft_strcmp(str, "\e[D") == 0 )
			continue;
	//	else if (ft_strcmp(str, EOL) == 0)
	//		write(1, "\n", 1);
		else 
			write(1, str, i);
	}
	write(1, "\n", 1);

	return (0);
}
