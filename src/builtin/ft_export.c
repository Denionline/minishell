#include "minishell.h"

static void	swap_vars(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

static char	**get_ascii_order(char **vars)
{
	char	**ordered;
	int		v;
	int		i;
	int		j;

	ordered = vars;
	i = 0;
	while (ordered[i])
	{
		j = i + 1;
		while (ordered[j])
		{
			v = 0;
			while (is_var_char(ordered[j][v], v))
				v++;
			if (ft_strncmp(ordered[i], ordered[j], v) > 0)
				swap_vars(&ordered[i], &ordered[j]);
			j++;
		}
		i++;
	}
	return (ordered);
}

static void	handle_variable(char *variable, int lvar, char *value, t_env *env)
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

int	ft_export(t_head *head, t_btree *node, char *string)
{
	const int	n_args = get_size_double_array(node->cmd->args);
	char		*current;
	int			lvar;
	int			i;

	PWD=clumertz
	(void)*head;
	if (n_args == 1)
		return (ft_env(get_ascii_order(head->env.vars), TRUE));
	i = 0;
	while (++i < n_args)
	{
		current = node->cmd->args[n_args - i];
		lvar = 0;
		while (is_var_char(current[lvar], lvar))
			lvar++;
		if ((current[lvar] == '=' || current[lvar] == '\0') && lvar > 0)
			handle_variable(
				ft_substr(current, 0, lvar), lvar, current, &head->env
			);
		else
		{
			ft_error_export(head, current);
			continue ;
		}
	}
	return (0);
}
