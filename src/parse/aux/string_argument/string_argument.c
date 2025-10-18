
#include "minishell.h"

static int	is_to_handle_variable(t_arg *arg, char *s, char quote, char **envp)
{
	if (!envp)
		return (FALSE);
	if (s[arg->i] == '$' && quote != '\'')
	{
		if (!s[arg->i + 1])
			return (FALSE);
		if (!is_var_char(s[arg->i + 1]))
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

static int	variable(t_arg *arg, char *string, char **envp)
{
	char	*prefix;
	char	*name;
	char	*variable;
	int		var_size;
	int		i;

	var_size = arg->i + 1;
	while (string[var_size] && is_var_char(string[var_size]))
		var_size++;
	var_size -= (arg->i + 1);
	name = ft_substr(string + arg->i + 1, 0, var_size);
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
	return (free(name), free(prefix), free(variable), var_size + arg->i);
}

char	*string_argument(char *string, char **envp, int *len)
{
	t_arg	arg;

	ft_bzero(&arg, sizeof(arg));
	arg.lstring = string_argument_size(string, envp);
	arg.string = ft_calloc(arg.lstring + 1, 1);
	if (!arg.string)
		return (NULL);
	arg.i = -1;
	while (string[++arg.i] && arg.pos < arg.lstring)
	{
		if (is_tohandle_backslash(string + arg.i, arg.quotes.quote))
			arg.i++;
		if (string[arg.i] == '\'' || string[arg.i] == '\"')
			if (!verify_quotes(&arg.quotes, string[arg.i]))
				continue ;
		if (is_main_quote_closed(&arg.quotes) && get_operator(string + arg.i))
			break ;
		if (is_main_quote_closed(&arg.quotes) && ft_isspace(string[arg.i]))
			break ;
		if (is_to_handle_variable(&arg, string, arg.quotes.quote, envp))
			arg.i = variable(&arg, string, envp);
		else
			arg.string[arg.pos++] = string[arg.i];
	}
	arg.string[arg.pos] = '\0';
	if (len)
		*len += arg.i;
	return (arg.string);
}
//  echo 'hel' $SHELL 'lo'
//  "e"c'h'"o" "hel' $SHELL 'lo"
//  "e"c'h'"o" hel' $SHELL 'lo