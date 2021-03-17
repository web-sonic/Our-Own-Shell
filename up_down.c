#include "minishell.h"
#include <string.h>

int
	ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

void
	puts_line(char *str)
{
	int i;

	i = read(0, str, 100);
	if (ft_strcmp(str, "\e[A") == 0)
	{
		tputs(restore_cursor, 1, ft_putchar);
		//tputs(delete_line, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		write(1, "up", 3);
	}
	else if (ft_strcmp(str, "\e[B") == 0)
	{
		tputs(restore_cursor, 1, ft_putchar);
		//tputs(delete_line, 1, ft_putchar);
		tputs(tigetstr("ed"), 1, ft_putchar);
		write(1, "down", 5);
	}
	else if (ft_strcmp(str, "\e[C") == 0 || ft_strcmp(str, "\e[D") == 0 )
		return;
	else
		write(1, str, i);
}

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
	while(ft_strncmp(str, "\4", 2))
	{
		tputs(save_cursor, 1, ft_putchar);
		//Это было в do while
		puts_line(str);
		//tputs(save_cursor, 1, ft_putchar);
		while (ft_strcmp(str, "\n"))
		{
			puts_line(str);
		}
	}
	write(1, "\n", 1);

	return (0);
}
