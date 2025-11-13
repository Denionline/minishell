#include "minishell.h"

int	ft_env(char **env, int by_export)
{
	int	i;
	int	j;

	i = -1;
	while (env && env[++i])
	{
		if (!by_export)
		{
			j = 0;
			while (is_var_char(env[i][j], j))
				j++;
			if (env[i][j] != '=')
				continue ;
		}
		else
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
		}
		ft_putendl_fd(env[i], STDOUT_FILENO);
	}
	return (0);
}
