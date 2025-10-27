
#include "minishell.h"

int	is_variable_exist(char *variable, char **vars)
{
	char	*name;
	int		lname;
	int		pos;
	
	name = ft_strjoin(variable, "=");
	lname = ft_strlen(name);
	pos = 0;
	while (vars[pos])
	{
		if (!ft_strncmp(name, vars[pos], lname))
		{
			free(name);
			return (pos);
		}
		pos++;
	}
	free(name);
	return (-1);
}
