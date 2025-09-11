
#include "minishell.h"

int	get_array_len(char **array)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (array[i])
	{
		if (!is_signal(array[i]) && (is_signal(array[i + 1]) || !array[i + 1]))
			len++;
		i++;
	}
	return (len);
}
