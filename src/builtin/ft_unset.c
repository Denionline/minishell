
#include "minishell.h"

static void	remove_variable(t_env **env, char *variable_to_remove)
{
	char	**new_vars;
	int		pos_var;
	int		i;

	pos_var = is_variable_exist(variable_to_remove, (*env)->vars);
	if (pos_var < 0)
		return (free(variable_to_remove));
	printf("Var => %s on the pos => %d\n", (*env)->vars[pos_var], pos_var);
	(*env)->n_vars -= 1;
	new_vars = ft_calloc((*env)->n_vars + 1, 1);
	if (!new_vars)
		return ;
	i = 0;
	while ((*env)->vars[i])
	{
		if (pos_var != i)
			new_vars[i] = (*env)->vars[i];
		i++;
	}
	(*env)->vars = new_vars;
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
		while (is_var_char(current[var_size]))
			var_size++;
		remove_variable(&env, ft_substr(current, 0, var_size + 1));
	}
	return (0);
}
