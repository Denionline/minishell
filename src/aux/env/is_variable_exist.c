
#include "minishell.h"

int	is_variable_exist(char *variable, char **vars)
{
	const int	lvariable = ft_strlen(variable);
	int		pos;
	
	pos = 0;
	while (vars[pos])
	{
		if (!ft_strncmp(variable, vars[pos], lvariable))
			return (pos);
		pos++;
	}
	return (-1);
}
