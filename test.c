#include "minishell.h"

int main()
{
	char *dir_pwd = calloc(sizeof(char), PATH_MAX);
	printf("%s \n", getcwd(dir_pwd, PATH_MAX - 1));
	chdir("../../../../../../tmp");
	free(dir_pwd);
	printf("%s \n", getcwd(dir_pwd, PATH_MAX - 1));
}