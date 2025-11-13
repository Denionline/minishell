#include "minishell.h"

int	is_var_char(char c, int pos)
{
	if (c == '_')
		return (TRUE);
	if (pos == 0 && ft_isalpha(c))
		return (TRUE);
	if (pos > 0 && ft_isalnum(c))
		return (TRUE);
	return (FALSE);
}
