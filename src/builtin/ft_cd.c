
#include "minishell.h"

void	ft_cd(char *path)
{
	chdir(path);
	exit(0);
}

/*
int	main(void)
{
	char buffer[100];

	printf("initial %s\n", getcwd(buffer, 100));
	chdir("..");
	printf("final %s\n", getcwd(buffer, 100));
	return (0);
}*/
