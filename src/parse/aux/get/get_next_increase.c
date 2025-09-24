
#include "minishell.h"

int	get_next_increase(int operator)
{
	if (operator == AND)
		return (operator_size(operator));
	if (operator == OR)
		return (operator_size(operator));
	if (operator == DOUBLE_ARROW_LEFT)
		return (operator_size(operator));
	if (operator == DOUBLE_ARROW_RIGHT)
		return (operator_size(operator));
	if (operator == ARROW_RIGHT)
		return (operator_size(operator));
	if (operator == ARROW_LEFT)
		return (operator_size(operator));
	return (1);
}
