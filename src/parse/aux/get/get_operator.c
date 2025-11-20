/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:10:14 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 12:10:14 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_operator_size(int operator)
{
	if (operator == 0)
		return (0);
	if (operator == DOUBLE_ARROW_LEFT)
		return (2);
	if (operator == DOUBLE_ARROW_RIGHT)
		return (2);
	return (1);
}

int	is_arrow_operator(int operator)
{
	if (operator == ARROW_LEFT)
		return (TRUE);
	if (operator == ARROW_RIGHT)
		return (TRUE);
	if (operator == DOUBLE_ARROW_LEFT)
		return (TRUE);
	if (operator == DOUBLE_ARROW_RIGHT)
		return (TRUE);
	return (FALSE);
}

int	get_operator(char *value)
{
	if (value[0] == '|')
		return (PIPE);
	if (value[0] == '<' && value[1] == '<')
		return (DOUBLE_ARROW_LEFT);
	if (value[0] == '>' && value[1] == '>')
		return (DOUBLE_ARROW_RIGHT);
	if (value[0] == '<')
		return (ARROW_LEFT);
	if (value[0] == '>')
		return (ARROW_RIGHT);
	return (0);
}
