
#include "minishell.h"

static char	*get_newlvl_string(char *variable, int newlvl)
{
	char	*string_number;
	char	*newlvl_string;

	string_number = ft_itoa(newlvl);
	ft_putstr_fd("SHLVL => ", 1);
	ft_putendl_fd(string_number, 1);
	newlvl_string = ft_strjoin("SHLVL=", string_number);
	free(string_number);
	free(variable);
	return (newlvl_string);
}

void	new_shlvl(char **env)
{
	const char	*prefix = "SHLVL=";
	const int	lprefix = ft_strlen(prefix);
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(prefix, env[i], lprefix))
			env[i] = get_newlvl_string(env[i], ft_atoi(env[i] + lprefix) + 1);
		i++;
	}
}
