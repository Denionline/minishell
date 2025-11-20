/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_var_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:22:10 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 19:34:49 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_char(char c, int pos)
{
	if (c == '_')
		return (TRUE);
	if (pos == 0 && ft_isalpha(c))
		return (TRUE);
	if (pos > 0 && ft_isalnum(c))
		return (TRUE);
	return (FALSE);
}

int	get_variable_size(char *string)
{
	int	len;

	if (string[1] == '\"' && string[2] == '\"')
		return (2);
	if (string[1] == '\'' && string[2] == '\'')
		return (2);
	len = 1;
	while (string[len] && is_var_char(string[len], len))
		len++;
	return (len);
}