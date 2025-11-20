/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_tohandle_backslash.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:11:04 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 12:11:05 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_tohandle_backslash(char *c, char quote)
{
	if (*c != '\\' || quote == '\'')
		return (0);
	c++;
	if (*c == '\"')
		return (1);
	if (*c == '\'')
		return (1);
	if (*c == '$')
		return (1);
	if (*c == '\\')
		return (1);
	if (*c == 'n')
		return (1);
	return (0);
}
