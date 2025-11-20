/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:22:04 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:22:05 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_db_str(char **db_str)
{
	int	i;

	i = 0;
	while (db_str[i])
	{
		free(db_str[i]);
		i++;
	}
	free(db_str);
}

void	free_node(t_btree *node)
{
	if (node->files.in.operator == DOUBLE_ARROW_LEFT)
		unlink(node->files.in.name);
	if (node->files.in.exists)
		free(node->files.in.name);
	if (node->files.out.exists)
		free(node->files.out.name);
	if (node->cmd)
	{
		if (node->cmd->args)
			free_db_str(node->cmd->args);
		if (node->cmd->path)
			free(node->cmd->path);
		free(node->cmd);
	}
	free(node);
}

void	free_btree(t_btree *node)
{
	if (node->left)
	{
		free_btree(node->left);
		if (node->right)
			free_btree(node->right);
	}
	if (node)
		free_node(node);
}

void	free_head(t_head *head)
{
	if (head->pid)
		free(head->pid);
	if (head->env.vars)
		free_db_str(head->env.vars);
	free(head);
}

void	free_error(t_head *head, t_btree *node, int *fd)
{
	close_all(head, node, fd);
	free_btree(head->root);
	free_db_str(head->env.vars);
	free(head);
}
