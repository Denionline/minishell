
#include "minishell.h"

int	is_operator(char *value)
{
	if (!ft_strncmp("&&", value - 1, 2))
		return (2);
	if (!ft_strncmp("|", value, 1))
	{
		if (!ft_strncmp("||", value - 1, 2))
			return (2);
		return (1);
	}
	if (!ft_strncmp("<<", value - 1, 2))
		return (2);
	if (!ft_strncmp(">>", value - 1, 2))
		return (2);
	if (!ft_strncmp("<", value, 1))
		return (1);
	if (!ft_strncmp(">", value, 1))
		return (1);
	return (0);
}
