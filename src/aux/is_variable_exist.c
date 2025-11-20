/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_variable_exist.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:22:09 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:22:10 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_variable_exist(char *variable, char **vars)
{
	const int	lvariable = ft_strlen(variable);
	int			pos;

	pos = -1;
	while (vars[++pos])
	{
		if (!ft_strncmp(variable, vars[pos], lvariable))
		{
			if (vars[pos][lvariable] == '=' || vars[pos][lvariable] == '\0')
				return (pos);
		}
	}
	return (-1);
}
