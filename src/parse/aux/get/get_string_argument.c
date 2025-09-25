
#include "minishell.h"

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

char	*get_string_argument(char *string)
{
	t_quotes	quotes;
	char		*string_argument;
	int			size;
	int			i;

	ft_bzero(&quotes, sizeof(quotes));
	size = 0;
	while (string[size])
	{
		if (is_main_quote_closed(&quotes) && get_operator(string + size))
			break ;
		if (is_main_quote_closed(&quotes) && ft_isspace(string[size]))
			break ;
		if (string[size] == '\'' || string[size] == '\"')
			verify_quotes(&quotes, string[size]);
		size++;
	}
	string_argument = ft_calloc(size + 1, 1);
	if (!string_argument)
		return (NULL);
	i = 0;
	while (i < size)
	{
		string_argument[i] = string[i];
		i++;
	}
	string_argument[i] = '\0';
	return (string_argument);
}
