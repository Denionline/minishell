
#include "minishell.h"

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		ft_putendl_fd(env[i++], STDOUT_FILENO);
}