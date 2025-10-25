
#include "minishell.h"

static int	is_to_handle_variable(t_arg *arg, char *s, char **envp, int expand)
{
	if (!expand)
		return (FALSE);
	if (!envp)
		return (FALSE);
	if (s[0] == '$' && arg->quotes.quote != '\'')
	{
		if (!s[1])
			return (FALSE);
		if (!is_var_char(s[1]))
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

static int	variable(t_arg *arg, char *string, char **envp)
{
	char	*variable;
	char	*prefix;
	char	*name;
	int		var_size;
	int		i;

	var_size = 1;
	while (string[var_size] && is_var_char(string[var_size]))
		var_size++;
	name = ft_substr(string, 1, var_size - 1);
	if (!name)
		return (free(arg->string), 0);
	prefix = ft_strjoin(name, "=");
	if (!prefix)
		return (free(name), 0);
	variable = get_var_path(prefix, envp);
	if (!variable)
		return (free(prefix), 0);
	i = 0;
	while (variable[i])
		arg->string[arg->pos++] = variable[i++];
	return (free(name), free(prefix), free(variable), var_size);
}

static char	*argument_verification(t_arg *arg, char *string, char **envp)
{
	if (is_tohandle_backslash(string, arg->quotes.quote))
		string++;
	if (string[0] == '\'' || string[0] == '\"')
		if (!verify_quotes(&arg->quotes, string[0], !arg->len))
			return (string);
	if (is_quote_closed(&arg->quotes) && get_operator(string) && arg->len)
		return (NULL);
	if (is_quote_closed(&arg->quotes) && ft_isspace(string[0]) && arg->len)
		return (NULL);
	if (is_to_handle_variable(arg, string, envp, arg->to_expand))
		string += variable(arg, string, envp);
	arg->string[arg->pos++] = string[0];
	return (string);
}

char	*string_argument(char *string, char **envp, int *len, int to_expand)
{
	char	*string_updated;
	t_arg	arg;
	int		i;

	ft_bzero(&arg, sizeof(arg));
	arg = (t_arg){.to_expand = to_expand, .len = len};
	string_argument_size(&arg, string, envp);
	arg.string = ft_calloc(arg.lstring + 1, 1);
	if (!arg.string)
		return (NULL);
	i = 0;
	while (string[i] && arg.pos <= arg.lstring)
	{
		string_updated = argument_verification(&arg, string + i, envp);
		if (!string_updated)
			break;
		if (string_updated - string)
			i = (string_updated - string);
		i += 1;
	}
	arg.string[arg.pos - (arg.string[arg.pos - 1] == arg.quotes.quote)] = '\0';
	if (len && to_expand)
		*len += i;
	return (arg.string);
}
