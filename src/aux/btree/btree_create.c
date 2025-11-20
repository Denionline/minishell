/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:21:25 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:54:47 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*btree_create(int id, t_cmd *cmd, t_btree *left, t_btree *right)
{
	t_btree	*new_token;

	new_token = ft_calloc(1, sizeof(t_btree));
	if (!new_token)
		return (NULL);
	new_token->identifier = id;
	new_token->cmd = cmd;
	new_token->left = left;
	new_token->right = right;
	new_token->files = (t_files){
		.in.fd = -1,
		.out.fd = -1
	};
	return (new_token);
}
