/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quotes_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:22:12 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 12:07:41 by dximenes         ###   ########.fr       */
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
		if (s[i] == '\'' || s[i] == '\"')
			verify_quotes(&quotes, s[i], FALSE);
		i++;
	}
	if ((quotes.s % 2) == 0 && (quotes.d % 2) == 0)
		return (TRUE);
	return (FALSE);
}
