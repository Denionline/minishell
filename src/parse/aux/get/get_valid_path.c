#include "minishell.h"

static char	*is_path_already(char *command)
{
	DIR	*dir;

	dir= opendir(command);
	if (dir)
	{
		closedir(dir);
		return (ft_strdup("dir"));
	}
	if (!access(command, F_OK | X_OK))
		return (ft_strdup(command));
	if (command[0] == '.' && !access(command, F_OK | X_OK))
		return (ft_strdup(command));
	if (is_builtin(command))
		return (ft_strdup("built-in"));
	return (NULL);
}

static char	**get_paths(t_env *env)
{
	char	*variable;
	char	*prefix;
	char	**paths;

	prefix = ft_strdup("PATH");
	variable = get_var_path(prefix, env->vars);
	free(prefix);
	if (!variable)
		return (NULL);
	paths = ft_split(variable, ':');
	free(variable);
	return (paths);
}

char	*get_valid_path(t_env *env, char *command)
{
	char	*complete_path;
	char	*path_bar;
	char	**paths;
	int		i;

	if (!command)
		return (NULL);
	complete_path = is_path_already(command);
	if (complete_path)
		return (complete_path);
	paths = get_paths(env);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		path_bar = ft_strjoin(paths[i], "/");
		complete_path = ft_strjoin(path_bar, command);
		free(path_bar);
		if (!access(complete_path, F_OK | X_OK))
		{
			free_db_str(paths);
			return (complete_path);
		}
		free(complete_path);
	}
	free_db_str(paths);
	return (NULL);
}
