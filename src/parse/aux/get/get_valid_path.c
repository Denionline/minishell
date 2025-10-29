
#include "minishell.h"

char	*get_valid_path(t_env *env, char *command)
{
	char	*complete_path;
	char	*path_bar;
	char	**paths;
	int		i;

	if (!command)
		return (NULL);
	if (!access(command, F_OK | X_OK))
		return (command);
	if (command[0] == '.' && !access(command, F_OK | X_OK))
		return (command);
	if (is_builtin(command))
		return (ft_strdup("built-in"));
	paths = ft_split(get_var_path("PATH", env->vars), ':');
	i = -1;
	while (paths[++i])
	{
		path_bar = ft_strjoin(paths[i], "/");
		complete_path = ft_strjoin(path_bar, command);
		free(path_bar);
		if (!access(complete_path, F_OK | X_OK))
			return (complete_path);
		free(complete_path);
	}
	return (NULL);
}
