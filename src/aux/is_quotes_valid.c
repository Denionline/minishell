/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quotes_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:15:56 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 14:20:07 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quotes_valid(char *s)
{
	t_quotes	quotes;
	int			i;

	quotes = (t_quotes){};
	i = 0;
	while (s[i])
	{
		if (is_tohandle_backslash(s + i, quotes.quote))
			i++;
		else
		{
			if (s[i] == '\'' || s[i] == '\"')
				verify_quotes(&quotes, s[i], FALSE);
		}
		i++;
	}
	if ((quotes.s % 2) == 0 && (quotes.d% 2) == 0)
		return (TRUE);
	return (FALSE);
}
