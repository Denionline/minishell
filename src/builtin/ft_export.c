#include "minishell.h"

static void	change_or_set(char *variable, int lvar, char *value, t_env *env)
{
	int		pos;

	pos = is_variable_exist(variable, env->vars);
	if (pos >= 0)
	{
		if (value[lvar] == '=')
		{
			free(env->vars[pos]);
			env->vars[pos] = ft_strdup(value);
		}
	}
	else
	{
		env->vars = get_realloc_args(
			env->vars,
			++env->n_vars,
			ft_strdup(value)
		);
	}
	free(variable);
}

static int	handle_variable(t_head *head, char *complete_var)
{
	int	lvar;

	lvar = 0;
	while (is_var_char(complete_var[lvar], lvar))
		lvar++;
	if ((complete_var[lvar] == '=' || complete_var[lvar] == '\0') && lvar > 0)
		change_or_set(
			ft_substr(complete_var, 0, lvar), lvar, complete_var, &head->env
		);
	else
		ft_error(head, (t_error){.id = 15, .string = complete_var});
	return (0);
}

int	ft_export(t_head *head, t_btree *node, char *variable_to_change)
{
	int	n_args;
	int	i;
	
	if (variable_to_change)
		return (handle_variable(head, variable_to_change));
	n_args = get_size_double_array(node->cmd->args);
	if (n_args == 1)
		return (ft_env(get_ascii_order(head->env.vars), TRUE));
	i = 0;
	while (++i < n_args)
		handle_variable(head, node->cmd->args[n_args - i]);
	return (0);
}
