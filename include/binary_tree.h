/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:43:18 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 12:35:58 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_H
# define BINARY_TREE_H

# include "minishell.h"

t_btree	*btree_create(int id, t_cmd *cmd, t_btree *left, t_btree *right);
void	btree_add_as_first(t_btree **root, t_btree *new_node);
void	btree_set_file_last_cmd(t_btree **root, t_files **files);

#endif
