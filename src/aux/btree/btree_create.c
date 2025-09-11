/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:31:48 by dximenes          #+#    #+#             */
/*   Updated: 2025/09/10 16:26:51 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*btree_create(char *identifier, t_cmd *cmd, t_token *left, t_token *right)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->identifier = identifier;
	new_token->cmd = cmd;
	new_token->left = left;
	new_token->right = right;
	return (new_token);
}
