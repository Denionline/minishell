
#include "minishell.h"

static int	get_number_of_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

static t_env	handle_variable(char *var, int lvar, char *value, t_env *env)
{
	t_env	new_env;

	ft_bzero(&new_env, sizeof(new_env));
	while (env->vars[new_env.n_vars])
	{
		if (!ft_strncmp(var, env->vars[new_env.n_vars], lvar))
		{
			free(env->vars[new_env.n_vars]);
			env->vars[new_env.n_vars] = ft_strdup(value);
			return (free(var), (t_env){.n_vars = 0, .vars = NULL});
		}
		new_env.n_vars++;
	}
	new_env.vars = get_realloc_args(env->vars, new_env.n_vars, ft_strdup(value));
	free(var);
	return (new_env);
}
int	ft_export(t_cmd *cmd, t_env *env)
{
	const int	n_args = get_number_of_args(cmd->args);
	char		*current;
	int			var_size;
	int			i;

	i = 0;
	while (++i < n_args)
	{
		current = cmd->args[n_args - i];
		var_size = 0;
		while (is_var_char(current[var_size]))
			var_size++;
		if (current[var_size] != '=')
			return (1);
		(*env) = handle_variable(ft_substr(current, 0, var_size + 1),
			var_size,
			current,
			env
		);
	}
	return (0);
}
