
#include "minishell.h"

static void	handle_variable(char *variable, char *value, t_env *env)
{
	int		pos;

	pos = is_variable_exist(variable, env->vars);
	if (pos >= 0)
	{
		free(env->vars[pos]);
		env->vars[pos] = ft_strdup(value);
	}
	else
	{
		env->vars = get_realloc_args(env->vars,
			++env->n_vars,
			ft_strdup(value)
		);
	}
	free(variable);
}
int	ft_export(t_cmd *cmd, t_env *env)
{
	const int	n_args = get_size_double_array(cmd->args);
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
		{
			printf("%s: not a valid identifier\n", current);
			continue;
		}
		handle_variable(ft_substr(current, 0, var_size), current, env);
	}
	return (0);
}
