
#include "minishell.c"

void	ft_pwd(void)
{
	char	buffer[100];

	printf("%s\n", getcwd(buffer, 100));
}
/*
int	main()
{
	ft_pwd();
	return (0);
}*/
