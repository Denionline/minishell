
#include "minishell.h"

char	*get_valid_path(char **paths, char *command)
{
	char	*complete_path;
	char	*path_bar;
	int		j;

	j = 0;
	while (paths[j])
	{
		path_bar = ft_strjoin(paths[j], "/");
		complete_path = ft_strjoin(path_bar, command);
		free(path_bar);
		if (!access(complete_path, F_OK | X_OK))
			return (complete_path);
		free(complete_path);
		j++;
	}
	if (command[0] == '.' && !access(command, F_OK | X_OK))
		return (command);
	return (NULL);
}

