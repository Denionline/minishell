#include "minishell.h"

int	is_directory(char *string)
{
	DIR	*dir;

	if (ft_strchr(string, '/'))
	{
		dir = opendir(string);
		if (dir)
		{
			closedir(dir);
			return (TRUE);
		}
	}
	return (FALSE);
}
