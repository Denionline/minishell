/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_add_last_left.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:47:12 by dximenes          #+#    #+#             */
/*   Updated: 2025/09/13 12:35:01 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	btree_add_last_left(t_token **root, t_token *new_token)
{
	t_token	*temp;

	if (!(*root))
		(*root) = new_token;
	else
	{
		temp = *root;
		while (temp->left)
			temp = temp->left;
		temp->left = new_token;
	}
}
