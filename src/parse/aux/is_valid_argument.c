/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_argument.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:10:06 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/22 12:33:27 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_argument(t_head *head, char *arg, int op, int op_after)
{
	if (op == ANDPERCENT)
		return (FALSE);
	if (op == PIPE && !head->root)
		return (FALSE);
	if (!is_arrow_operator(op) && is_arrow_operator(op_after))
		return (TRUE);
	if (op_after)
		return (FALSE);
	if (*arg == '&')
		return (FALSE);
	if (*arg == '(' || *arg == ')')
		return (FALSE);
	if (!(*arg))
		return (FALSE);
	return (TRUE);
}
