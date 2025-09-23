
#include "minishell.h"

static char	*ft_strreplace(char *string, char search)
{
	char	*new_string;
	int		j;
	int		i;

	if (!string)
		return (NULL);
	if (search == '\0')
		return (string);
	i = 0;
	j = 0;
	while (string && string[j])
	{
		if (search && string[j] == search)
			i++;
		j++;
	}
	j -= i;
	new_string = ft_calloc(j + 1, 1);
	if (!new_string)
		return (NULL);
	j = 0;
	i = 0;
	while (string && string[i])
	{
		if (search && string[i] != search)
			new_string[j++] = string[i];
		i++;
	}
	new_string[j] = '\0';
	free(string);
	return (new_string);
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

char	*get_string_argument(char *string)
{
	t_quotes	quotes;
	char		quote;
	char		*arg;
	int			size;
	int			i;

	size = 0;
	ft_bzero(&quotes, sizeof(quotes));
	while (string[size])
	{
		if (quotes.quote)
			quote = quotes.quote;
		if (is_main_quote_closed(&quotes) && is_operator(string + size))
			break ;
		if (is_main_quote_closed(&quotes) && ft_isspace(string[size]))
			break ;
		if (string[size] == '\'' || string[size] == '\"')
			verify_quotes(&quotes, string[size]);
		size++;
	}
	arg = ft_calloc(size + 1, 1);
	if (!arg)
		return (NULL);
	i = 0;
	while (i < size)
	{
		arg[i] = string[i];
		i++;
	}
	arg[i] = '\0';
	return (ft_strreplace(arg, quote));
}
