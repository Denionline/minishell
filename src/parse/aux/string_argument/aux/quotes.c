#include "minishell.h"

int	is_quote_closed(t_quotes *quotes)
{
	if (!quotes->quote)
		return (TRUE);
	if (quotes->quote == '\'' && (quotes->s % 2) == 0)
		return (TRUE);
	if (quotes->quote == '\"' && (quotes->d % 2) == 0)
		return (TRUE);
	return (FALSE);
}

static void	increase_quote(t_quotes *quotes, char c)
{
	if (c == '\'' && quotes->quote == '\'')
		quotes->s += 1;
	else if (c == '\"' && quotes->quote == '\"')
		quotes->d += 1;
}

int	verify_quotes(t_quotes *quotes, char c, int is_heredoc)
{
	if (!quotes->quote && !is_heredoc)
	{
		quotes->quote = c;
		increase_quote(quotes, c);
		return (TRUE);
	}
	if (quotes->quote == c && !is_heredoc)
	{
		increase_quote(quotes, c);
		quotes->quote = '\0';
		return (TRUE);
	}
	return (FALSE);
}
