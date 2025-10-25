
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

int	verify_quotes(t_quotes *quotes, char c, int is_heredoc)
{
	int	verify;

	verify = 1;
	if (!quotes->quote && !is_heredoc)
	{
		quotes->quote = c;
		verify = 0;
	}
	else if (quotes->quote == c && !is_heredoc)
	{
		quotes->quote = '\0';
		verify = 0;
	}
	if (c == '\'' && quotes->quote == '\'')
		quotes->s += 1;
	else if (c == '\"' && quotes->quote == '\"')
		quotes->d += 1;
	return (verify);
}
