#include "minishell.h"

int	is_valid_argument(char *arg, int op, int op_after)
{
	if (!(*arg))
		return (FALSE);
	if (!is_arrow_operator(op) && is_arrow_operator(op_after))
		return (TRUE);
	if (op_after)
		return (FALSE);
	if (*arg == '&')
		return (FALSE);
	if (*arg == '(' || *arg == ')')
		return (FALSE);
	return (TRUE);
}
