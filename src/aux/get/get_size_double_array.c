#include "minishell.h"

int	get_size_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
