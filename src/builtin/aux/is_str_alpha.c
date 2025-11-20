/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_str_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:42:22 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:43:04 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_alpha(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (ft_isalpha(string[i]) == 1)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
