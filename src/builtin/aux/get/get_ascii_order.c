/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ascii_order.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:22:27 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:22:27 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_vars(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

char	**get_ascii_order(char **vars)
{
	char	**ordered;
	int		v;
	int		i;
	int		j;

	ordered = vars;
	i = 0;
	while (ordered[i])
	{
		j = i + 1;
		while (ordered[j])
		{
			v = 0;
			while (is_var_char(ordered[j][v], v))
				v++;
			if (ft_strncmp(ordered[i], ordered[j], v) > 0)
				swap_vars(&ordered[i], &ordered[j]);
			j++;
		}
		i++;
	}
	return (ordered);
}
