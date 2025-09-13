/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_add_last_right.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:47:12 by dximenes          #+#    #+#             */
/*   Updated: 2025/09/09 16:01:50 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	btree_add_last_right(t_token **root, t_token *new_token)
{
	t_token	*temp;

	if (!(*root))
		(*root) = new_token;
	else
	{
		temp = *root;
		while (temp->right)
			temp = temp->right;
		temp->right = new_token;
	}
}
