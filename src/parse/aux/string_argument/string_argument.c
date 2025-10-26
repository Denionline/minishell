
#include "minishell.h"

static int	is_to_handle_variable(t_arg *arg, char *s, char **envp, int expand)
{
	if (!expand)
		return (FALSE);
	if (!envp)
		return (FALSE);
	if (s[0] == '$' && arg->quotes.quote != '\'')
	{
		if (s[1] == '?')
			return (TRUE);
		if (!s[1])
			return (FALSE);
		if (!is_var_char(s[1]))
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

static int	variable(t_arg *arg, char *string, t_head *head)
{
	char	*variable;
	char	*name;
	int		var_size;
	int		i;

	var_size = 1;
	while (string[var_size] && is_var_char(string[var_size++]))
		if (string[1] == '?')
			break;
	name = ft_substr(string, 1, var_size - 1);
	if (!name)
		return (free(arg->string), 0);
	if (string[1] == '?')
		variable = ft_itoa(head->exit_code);
	else
		variable = get_var_path(name, head->env.vars);
	if (!variable)
		return (free(name), 0);
	i = 0;
	while (variable[i])
		arg->string[arg->pos++] = variable[i++];
	return (free(name), free(variable), var_size);
}

static char	*argument_verification(t_arg *arg, char *string, t_head *head)
{
	if (is_tohandle_backslash(string, arg->quotes.quote))
		string++;
	if (*string == '\'' || *string == '\"')
		if (!verify_quotes(&arg->quotes, *string, !arg->len))
			return (string);
	if (is_quote_closed(&arg->quotes) && get_operator(string) && arg->len)
		return (NULL);
	if (is_quote_closed(&arg->quotes) && ft_isspace(*string) && arg->len)
		return (NULL);
	if (is_to_handle_variable(arg, string, head->env.vars, arg->to_expand))
		string += variable(arg, string, head);
	arg->string[arg->pos++] = *string;
	return (string);
}

char	*string_argument(t_head *head, char *string, t_arg arg)
{
	char	*string_updated;
	int		i;

	string_argument_size(&arg, string, head->env.vars);
	arg.string = ft_calloc(arg.lstring + 1, 1);
	if (!arg.string)
		return (NULL);
	i = 0;
	while (string[i] && arg.pos <= arg.lstring)
	{
		string_updated = argument_verification(&arg, string + i, head);
		if (!string_updated)
			break;
		if (string_updated - string)
			i = (string_updated - string);
		i += 1;
	}
	arg.string[arg.pos - (arg.string[arg.pos - 1] == arg.quotes.quote)] = '\0';
	if (arg.len && arg.to_expand)
		*(arg.len) += i;
	return (arg.string);
}
