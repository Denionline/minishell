/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_add_last_left.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:47:12 by dximenes          #+#    #+#             */
/*   Updated: 2025/09/10 13:48:55 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	btree_add_last_left(t_token **root, t_token *new_token)
{
	if (!(*root))
		(*root) = new_token;
	else
	{
		while((*root)->left)
			(*root) = (*root)->left;
		(*root)->left = new_token;
	}
}
