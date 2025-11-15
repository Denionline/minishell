#include "minishell.h"

static void	remove_variable(t_env **env, char *variable_to_remove)
{
	char	**new_vars;
	char	**old_vars;
	int		pos_var;
	int		pos;
	int		i;

	pos_var = is_variable_exist(variable_to_remove, (*env)->vars);
	if (pos_var < 0)
		return (free(variable_to_remove));
	(*env)->n_vars -= 1;
	old_vars = (*env)->vars;
	new_vars = ft_calloc((*env)->n_vars + 1, sizeof(char *));
	if (!new_vars)
	{
		free(variable_to_remove);
		return ;
	}
	pos = 0;
	i = 0;
	while (old_vars[i])
	{
		if (i != pos_var)
			new_vars[pos++] = old_vars[i];
		i++;
	}
	new_vars[pos] = NULL;
	free(old_vars[pos_var]);
	free(old_vars);
	(*env)->vars = new_vars;

	/* free the substring passed by the caller (ft_substr) */
	free(variable_to_remove);
}

int	ft_unset(t_cmd *cmd, t_env *env)
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
		while (is_var_char(current[var_size], var_size))
			var_size++;
		remove_variable(&env, ft_substr(current, 0, var_size));
	}
	return (define_exit_code(0, TRUE));
}
