
#include "minishell.h"

typedef struct s_arg {
	char	*string;
	int		lstring;
	int		lvariables;
	int		pos;
	int		i;
}	t_arg;

static int	is_tohandle_backslash(char *c, char quote)
{
	if (*c != '\\' || quote == '\'')
		return (0);
	c++;
	if (*c == '\"')
		return (1);
	if (*c == '\'')
		return (1);
	if (*c == '$')
		return (1);
	if (*c == '\\')
		return (1);
	if (*c == 'n')
		return (1);
	return (0);
}

static void	verify_quotes(t_quotes *quotes, char c)
{
	if (c == '\'')
		quotes->s += 1;
	if (c == '\"')
		quotes->d += 1;
	if (!quotes->quote)
		quotes->quote = c;
	else if (quotes->quote == c)
		quotes->quote = '\0';
}

static int	is_main_quote_closed(t_quotes *quotes)
{
	if (!quotes->quote)
		return (TRUE);
	if (quotes->quote == '\'' && (quotes->s % 2) == 0)
		return (TRUE);
	if (quotes->quote == '\"' && (quotes->d % 2) == 0)
		return (TRUE);
	return (FALSE);
}

static int	get_string_argument_size(char *string, char **envp)
{
	t_quotes	quotes;
	int			size;
	int			jumps;
	
	ft_bzero(&quotes, sizeof(quotes));
	jumps = 0;
	size = 0;
	while (string[size])
	{
		if (is_tohandle_backslash(string + size, quotes.quote))
			jumps += 1;
		if (is_main_quote_closed(&quotes) && get_operator(string + size))
			break ;
		if (is_main_quote_closed(&quotes) && ft_isspace(string[size]))
			break ;
		if (string[size] == '\'' || string[size] == '\"')
			verify_quotes(&quotes, string[size]);
		size += 1;
	}
	if (!envp && (string[size] == '\'' || string[size] == '\"'))
		size -= 1;
	return (size - jumps);
}

static char	*join_var(t_arg *arg, char *string,char **envp)
{
	char	*new_string;
	char	*variable;
	char	*prefix;
	char	*temp;
	int		size;

	temp = get_string_argument(string + 1, NULL);
	arg->i += ft_strlen(temp);
	prefix = ft_strjoin(temp, "=");
	free(temp);
	variable = get_var_path(prefix, envp);
	free(prefix);
	size = ft_strlen(variable);
	new_string = ft_strjoin(arg->string, variable);
	free(arg->string);
	free(variable);
	arg->lvariables += size;
	return (new_string);
}

char	*get_string_argument(char *string, char **envp)
{
	t_arg	arg;
	
	ft_bzero(&arg, sizeof(arg));
	arg.lstring = get_string_argument_size(string, envp);
	arg.string = ft_calloc(arg.lstring + 1, 1);
	if (!arg.string)
		return (NULL);
	while (arg.pos < arg.lstring + arg.lvariables)
	{
		if (envp && string[arg.i] == '$' && string[arg.i] != '\\')
			arg.string = join_var(&arg, string + arg.i, envp);
		else if (!is_tohandle_backslash(string + arg.i, string[0]) || arg.i == arg.lstring - 1)
			arg.string[arg.pos] = string[arg.i];
		arg.pos = (++arg.i + arg.lvariables);
	}
	arg.string[arg.pos] = '\0';
	return (arg.string);
}
