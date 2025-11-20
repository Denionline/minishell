/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:21:58 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 19:17:16 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_manager(t_head *head)
{
	signal(SIGINT, SIG_IGN);
	if (!head->root)
		return ;
	if (head->to_stop == TRUE)
	{
		free_btree(head->root);
		head->root = NULL;
		return ;
	}
	reset_head(head);
	hierarchy_btree(head, head->root);
	wait_process(head);
	close_all(head, NULL, NULL);
	free_btree(head->root);
	head->root = NULL;
}

int	hierarchy_btree(t_head *head, t_btree *node)
{
	if (node == NULL)
		return (0);
	else if (node->identifier == COMMAND)
		process(head, node);
	else if (node->left && node->left->identifier == PIPE)
		hierarchy_btree(head, node->left);
	if (node->left && node->left->identifier == COMMAND)
	{
		process(head, node->left);
		if (node->right->identifier == COMMAND)
			process(head, node->right);
		node = NULL;
	}
	if (node && node->right && node->right->identifier == COMMAND)
		process(head, node->right);
	return (define_exit_code(0, FALSE));
}

int	wait_process(t_head *head)
{
	int	status;
	int	exit_status;
	int	i;

	if (head->is_parent == 0)
		return (define_exit_code(0, FALSE));
	i = 0;
	while (i < head->n_cmds)
	{
		waitpid(head->pid[i], &status, 0);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_status = WTERMSIG(status) + 128;
		i++;
	}
	return (define_exit_code(exit_status, TRUE));
}
