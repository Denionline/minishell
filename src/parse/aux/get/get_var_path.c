
#include "minishell.h"

char	*get_var_path(char *prefix, char **envp)
{
	char	*name;
	int		lname;
	int		i;

	name = ft_strjoin(prefix, "=");
	lname = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, lname))
		{
			free(name);
			return (ft_strdup(envp[i] + lname));
		}
		i++;
	}
	return (NULL);
}
