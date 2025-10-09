
#include "minishell.h"

char	*get_var_path(char *prefix, char **envp)
{
	const int	lprefix = ft_strlen(prefix);
	int			i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], prefix, lprefix))
			return (ft_strdup(envp[i] + lprefix));
		i++;
	}
	return ("");
}
