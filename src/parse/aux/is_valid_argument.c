
#include "minishell.h"

int	is_valid_argument(char *arg)
{
	if (get_operator(arg))
		return (FALSE);
	if (*arg == '&')
		return (FALSE);
	if (*arg == '(' || *arg == ')')
		return (FALSE);
	if (!(*arg))
		return (FALSE);
	return (TRUE);
}
