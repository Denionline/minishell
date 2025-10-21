
#include "minishell.h"

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env && env[i]) {
		ft_putstr_fd("env[", STDOUT_FILENO);
		ft_putnbr_fd(i, STDOUT_FILENO);
		ft_putstr_fd("] => ", STDOUT_FILENO);
		ft_putendl_fd(env[i++], STDOUT_FILENO);
	}
}
