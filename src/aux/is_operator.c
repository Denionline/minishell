
#include "minishell.h"

int	operator_size(int operator)
{
	if (operator == 0)
		return (0);
	if (operator == AND)
		return (2);
	if (operator == OR)
		return (2);
	if (operator == DOUBLE_ARROW_LEFT)
		return (2);
	if (operator == DOUBLE_ARROW_RIGHT)
		return (2);
	return (1);
}

int	is_operator(char *value)
{
	if (!ft_strncmp("&&", value, 2))
		return (AND);
	if (!ft_strncmp("|", value, 1))
	{
		if (!ft_strncmp("||", value, 2))
			return (OR);
		return (PIPE);
	}
	if (!ft_strncmp("<<", value, 2))
		return (DOUBLE_ARROW_LEFT);
	if (!ft_strncmp(">>", value, 2))
		return (DOUBLE_ARROW_RIGHT);
	if (!ft_strncmp("<", value, 1))
		return (ARROW_LEFT);
	if (!ft_strncmp(">", value, 1))
		return (ARROW_RIGHT);
	return (0);
}
