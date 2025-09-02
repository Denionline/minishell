
#include "minishell.h"

int	get_array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}
