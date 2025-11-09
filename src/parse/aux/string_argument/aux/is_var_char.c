#include "minishell.h"

int	is_var_char(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}
