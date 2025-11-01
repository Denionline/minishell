
#include "minishell.h"

static int variable_size(char *string, char **envp)
{
	char	*name;
	char	*variable;
	int		var_size;

	var_size = 1;
	while (string[var_size] && is_var_char(string[var_size]))
		var_size++;
	name = ft_substr(string, 1, var_size - 1);
	if (name)
	{
		variable = get_var_path(name, envp);
		free(name);
		if (variable)
		{
			var_size = ft_strlen(variable);
			free(variable);
		}
	}
	return (var_size);
}

static int	argument_verification_size(t_arg *arg, char *string, char **envp)
{
	if (is_tohandle_backslash(string, arg->quotes.quote))
		string += 1;
	if (is_quote_closed(&arg->quotes) && get_operator(string) && arg->len)
		return (0);
	if (is_quote_closed(&arg->quotes) && ft_isspace(*string) && arg->len)
		return (0);
	if (*string == '\'' || *string == '\"')
	{
		if (!verify_quotes(&arg->quotes, *string, !arg->len))
			return (1);
	}
	if (*string == '$' && envp && arg->quotes.quote != '\'' && arg->to_expand)
		arg->lstring += variable_size(string, envp);
	return (1);
}

void	string_argument_size(t_arg *arg, char *string, char **envp)
{
	int	jumps;
	int	i;

	jumps = 0;
	i = -1;
	while (string[++i])
	{
		if (!argument_verification_size(arg, string + i, envp))
			break;
		arg->lstring += 1;
	}
//	if (!is_quote_closed(&arg->quotes))
//		printf("Command not found\n");
	arg->lstring -= jumps;
}
