#include "minishell.h"
#include <string.h>

int
	main(int ac, char **av, char **env)
{
	char	*str;
	//char	*course;
	char	*temp_name;
	int		i;
	struct	termios term;

	temp_name = strdup("xterm-256color");
	str = calloc(sizeof(char), 2000);
	if (!temp_name || !str)
		return (1);
	tcgetattr(0, &term);
	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~ICANON;
	tcsetattr(0, TCSANOW, &term);
	int n = 0;
	n = tgetent(0, temp_name);
	//course = key_up;
	//term.c_cc[VMIN] = 1;
	//term.c_cc[VTIME] = 0;
	//do
	while(strcmp(str, "\n"))
	{
		i = read(0, str, 100);
		if (strcmp(str, "\e[A") == 0)
			write(1, "up\n", 3);
		else if (strcmp(str, "\e[B") == 0)
			write(1, "down\n", 5);
		else 
			write(1, str, i);
	}
	write(1, "\n", 1);

	return (0);
}
