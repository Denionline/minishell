
#include "minishell.h"

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

static int	get_string_argument_size(char *string)
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
	return (size - jumps);
}

static char	*join_var(char *string, char **envp, int *var_len)
{
	char	*new_string;
	char	*variable;
	char	*prefix;
	char	*temp;
	int		size;

	string += 1;
	temp = get_string_argument(string, NULL);
	prefix = ft_strjoin(temp, "=");
	free(temp);
	variable = get_var_path(prefix, envp);
	free(prefix);
	size = ft_strlen(variable);
	new_string = ft_strjoin(string - size, variable);
	free(variable);
	*var_len += size;
	return (new_string);
}

char	*get_string_argument(char *string, char **envp)
{
	int		string_size;
	char	*string_argument;
	int		var_lengths;
	int		pos;
	
	string_size = get_string_argument_size(string);
	if (!envp && (string[string_size - 1] == '\'' || string[string_size - 1] == '\"'))
		string_size -= 1;
	string_argument = ft_calloc(string_size + 1, 1);
	if (!string_argument)
		return (NULL);
	var_lengths = 0;
	pos = 0;
	while (pos < string_size + var_lengths)
	{
		if (envp && string[pos] == '$' && string[pos - 1] != '\\')
			string_argument = join_var(string, envp, &var_lengths);
		else if (!is_tohandle_backslash(string + pos, string[0]) || pos == string_size - 1)
			string_argument[pos] = string[pos];
		pos += (1 + var_lengths);
	}
	string_argument[pos] = '\0';
	return (string_argument);
}
