
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
			while (is_var_char(ordered[j][v]))
				v++;
			if (ft_strncmp(ordered[i], ordered[j], v) > 0)
				swap_vars(&ordered[i], &ordered[j]);
			j++;
		}
		i++;
	}
	return (ordered);
}

static void	handle_variable(char *variable, char *value, t_env *env)
{
	int		pos;

	pos = is_variable_exist(variable, env->vars);
	ft_putnbr_fd(pos, 1);
	ft_putchar_fd('\n', 1);
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

	if (n_args == 1)
		return (ft_env(get_ascii_order(env->vars), TRUE));
	i = 0;
	while (++i < n_args)
	{
		current = cmd->args[n_args - i];
		var_size = 0;
		while (is_var_char(current[var_size]))
			var_size++;
		if (current[var_size] == '=' || current[var_size + 1] == '\0')
			handle_variable(ft_substr(current, 0, var_size), current, env);
		else
		{
			// ft_putchar_fd(current[var_size + 1], 1);
			ft_putendl_fd("Invalid variable", 1);
			continue;
		}
	}
	return (0);
}
