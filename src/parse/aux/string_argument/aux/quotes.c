/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:11:11 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 12:11:12 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
