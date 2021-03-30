#include "../minishell.h"

int main()
{
	char *dir_pwd = calloc(sizeof(char), PATH_MAX);
	getcwd(dir_pwd, PATH_MAX - 1);
	printf("%s\n",  dir_pwd);
	char *dir = "/Users/sgath";
	int ret = chdir(dir);
	free(dir_pwd);
	getcwd(dir_pwd, PATH_MAX - 1);
	printf("%s %d\n",  dir_pwd, ret);
}