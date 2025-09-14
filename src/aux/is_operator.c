
#include "minishell.h"

int	is_operator(char *value)
{
	if (!ft_strncmp("&&", value - 1, 2))
		return (AND);
	if (!ft_strncmp("|", value, 1) && ft_strncmp("|", value + 1, 1))
	{
		if (!ft_strncmp("||", value - 1, 2))
			return (OR);
		return (PIPE);
	}
	if (!ft_strncmp("<<", value - 1, 2))
		return (DOUBLE_ARROW_LEFT);
	if (!ft_strncmp(">>", value - 1, 2))
		return (DOUBLE_ARROW_RIGHT);
	if (!ft_strncmp("<", value, 1))
		return (ARROW_LEFT);
	if (!ft_strncmp(">", value, 1))
		return (ARROW_RIGHT);
	return (0);
}
