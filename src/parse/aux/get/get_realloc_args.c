
#include "minishell.h"

char	**get_realloc_args(char **old_args, int new_len, char *new_value)
{
	char	**new_args;
	int		i;

	(void)new_value;
	new_args = ft_calloc(new_len + 1, sizeof(char *));
	if (!new_args)
		return (NULL);
	if (old_args)
	{
		i = 0;
		while (old_args[i])
		{
			new_args[i] = old_args[i];
			i++;
		}
		free(old_args);
	}
	new_args[new_len - 1] = new_value;
	new_args[new_len] = NULL;
	return (new_args);
}
