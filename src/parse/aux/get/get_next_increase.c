
#include "minishell.h"

static int	get_size_file(char *prompt, int op_size)
{
	int	size;

	size = op_size;
	while (ft_isspace(prompt[size]))
		size += 1;
	while (prompt[size])
	{
		if (ft_isspace(prompt[size]))
			break ;
		size++;
	}
	return (size);
}

int	get_next_increase(int operator, char *prompt)
{
	if (operator == AND)
		return (operator_size(operator));
	if (operator == OR)
		return (operator_size(operator));
	if (operator == DOUBLE_ARROW_LEFT)
		return (operator_size(operator));
	if (operator == DOUBLE_ARROW_RIGHT)
		return (get_size_file(prompt, operator_size(operator)));
	if (operator == ARROW_RIGHT)
		return (get_size_file(prompt, operator_size(operator)));
	if (operator == ARROW_LEFT)
		return (get_size_file(prompt, operator_size(operator)));
	return (1);
}
