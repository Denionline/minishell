/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:21:44 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 19:17:04 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_head(t_head *head)
{
	head->files.in.fd = dup(STDIN_FILENO);
	head->files.out.fd = dup(STDOUT_FILENO);
	head->n_cmds = count_cmds(head->root, 0);
	head->pid = malloc(sizeof(pid_t) * head->n_cmds);
	if (!head->pid)
		return ;
	head->index = 0;
	head->is_parent = -1;
	head->pipe.pipe_fd[0] = -1;
	head->pipe.pipe_fd[1] = -1;
	head->pipe.flag = 0;
}

void	close_all_fds(t_head *head, t_btree *node, int process)
{
	if (head->pipe.pipe_fd[0] != -1)
		close(head->pipe.pipe_fd[0]);
	if (head->pipe.pipe_fd[1] != -1)
		close(head->pipe.pipe_fd[1]);
	if (node)
	{
		if (node->files.in.fd != -1)
			close(node->files.in.fd);
		if (node->files.out.fd != -1)
			close(node->files.out.fd);
	}
	if (process == 0)
	{
		close(head->files.in.fd);
		close(head->files.out.fd);
	}
	head->pipe.pipe_fd[0] = -1;
	head->pipe.pipe_fd[1] = -1;
}

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	close_all(t_head *head, t_btree *node, int *fd)
{
	dup2(head->files.in.fd, STDIN_FILENO);
	dup2(head->files.out.fd, STDOUT_FILENO);
	if (head->pid)
	{
		free(head->pid);
		head->pid = NULL;
	}
	if (head->pipe.flag == 1)
		close_fd(fd);
	close_all_fds(head, node, 0);
}

int	define_exit_code(int exit_status, int change)
{
	static int	exit_code;

	if (change == TRUE)
		exit_code = exit_status;
	return (exit_code);
}
