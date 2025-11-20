/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_add_as_first.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:21:19 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:21:19 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	btree_add_as_first(t_btree **root, t_btree *new_node)
{
	if (!(*root))
		(*root) = new_node;
	else
	{
		new_node->left = (*root);
		*root = new_node;
	}
}
