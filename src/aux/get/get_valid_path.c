#include "minishell.h"

static char	*is_path_already(char *command)
{
	if (is_directory(command))
		return (ft_strdup("dir"));
	if ((command[0] == '/' || command[1] == '/') && !access(command, F_OK))
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

static char	*get_complete_path(char *current_path, char *command)
{
	char	*complete_path;
	char	*path_bar;

	path_bar = ft_strjoin(current_path, "/");
	complete_path = ft_strjoin(path_bar, command);
	free(path_bar);
	if (!access(complete_path, F_OK | X_OK))
		return (complete_path);
	free(complete_path);
	return (NULL);
}

char	*get_valid_path(t_env *env, char *command)
{
	char	*valid_path;
	char	**paths;
	int		i;

	if (!command)
		return (NULL);
	valid_path = is_path_already(command);
	if (valid_path)
		return (valid_path);
	paths = get_paths(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		valid_path = get_complete_path(paths[i], command);
		if (valid_path)
			break ;
		i++;
	}
	free_db_str(paths);
	return (valid_path);
}
