
#include "minishell.h"

void	ft_pwd(t_btree *node)
{
	char	buffer[100];

	(void)*node;
	printf("%s\n", getcwd(buffer, 100));
	exit(0);
}
/*
int	main()
{
	ft_pwd();
	return (0);
}*/
