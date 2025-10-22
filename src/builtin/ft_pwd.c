
#include "minishell.h"

int	ft_pwd(t_btree *node)
{
	char	buffer[100];

	(void)*node;
	printf("%s\n", getcwd(buffer, 100));
	return(0);
}
/*
int	main()
{
	ft_pwd();
	return (0);
}*/
