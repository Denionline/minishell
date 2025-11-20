/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_var_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:22:10 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:22:11 by dximenes         ###   ########.fr       */
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
