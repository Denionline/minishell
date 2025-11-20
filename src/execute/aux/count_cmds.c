/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:22:32 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 19:16:59 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_btree *node, int j)
{
	static int	i;

	if (!node)
		return (0);
	i = j;
	if (node->identifier == COMMAND)
		i += 1;
	else if (node->identifier != COMMAND)
	{
		if (node->left)
			count_cmds(node->left, i);
		if (node->right)
			count_cmds(node->right, i);
	}
	return (i);
}
