
#include "minishell.h"

int	is_valid_argument(char *arg, int *op, int *pos)
{
	const int	op_found = get_operator(arg);

	if (!(*arg))
		return (FALSE);
	if (is_arrow_operator(*op) && is_arrow_operator(op_found))
		return (FALSE);
	if (!is_arrow_operator(*op) && is_arrow_operator(op_found))
	{
		*op = op_found;
		*pos += get_operator_size(op_found);
		return (TRUE);
	}
	if (op_found)
		return (FALSE);
	if (*arg == '&')
		return (FALSE);
	if (*arg == '(' || *arg == ')')
		return (FALSE);
	return (TRUE);
}
