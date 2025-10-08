
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

char	*get_string_argument(char *string)
{
	
	const int	string_size = get_string_argument_size(string);
	char		*string_argument;
	int			i;
	
	string_argument = ft_calloc(string_size + 1, 1);
	if (!string_argument)
		return (NULL);
	i = 0;
	while (i < string_size)
	{
		if (!is_tohandle_backslash(string + i, string[0]))
			string_argument[i] = string[i];
		i++;
	}
	string_argument[i] = '\0';
	return (string_argument);
}
