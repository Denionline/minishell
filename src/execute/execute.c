/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:22:01 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/21 18:03:58 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(t_head *head, t_btree *node, int *fd)
{
	if (node->files.in.exists)
	{
		node->files.in.fd = open(node->files.in.name, node->files.in.flags);
		if (node->files.in.fd == -1)
			ft_error(head,
				(t_error){.id = ERR_REDIR_IN, .node = node, .fds = fd});
		dup2(node->files.in.fd, STDIN_FILENO);
		close(node->files.in.fd);
	}
	if (node->files.out.exists)
	{
		node->files.out.fd = open(
				node->files.out.name, node->files.out.flags, 0664
				);
		if (node->files.out.fd == -1)
			ft_error(head,
				(t_error){.id = ERR_REDIR_OUT, .node = node, .fds = fd});
		dup2(node->files.out.fd, STDOUT_FILENO);
		close(node->files.out.fd);
	}
}

void	parent_process(t_head *head, t_btree *node, int *fd)
{
	close_all_fds(head, node, 1);
	if (head->pipe.flag == 1)
	{
		head->pipe.pipe_fd[0] = dup(fd[0]);
		head->pipe.pipe_fd[1] = dup(fd[1]);
		close_fd(fd);
	}
}

void	child_process(t_head *head, t_btree *node, int *fd)
{
	child_signal_handler();
	if (head->pipe.pipe_fd[0] != -1)
		dup2(head->pipe.pipe_fd[0], STDIN_FILENO);
	if (head->pipe.flag == 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_fd(fd);
	}
	if (node->files.in.exists || node->files.out.exists)
		redirect(head, node, fd);
	if (node->cmd->path && is_strmatch(node->cmd->path, "dir"))
		ft_error(head, (t_error){.id = ERR_DIR, .node = node, .fds = fd});
	if (node->cmd->args
		&& (node->cmd->args[0][0] == '/' || node->cmd->args[0][1] == '/'))
	{
		if (access(node->cmd->args[0], F_OK))
			ft_error(head,
				(t_error){.id = ERR_NOT_FOUND, .node = node, .fds = fd});
		else if (access(node->cmd->args[0], X_OK))
			ft_error(head, (t_error){.id = ERR_PER, .node = node, .fds = fd});
	}
	if (!node->cmd->path && !node->files.in.exists && !node->files.out.exists)
		ft_error(head, (t_error){.id = ERR_CMD, .node = node, .fds = fd});
	close_all_fds(head, node, 0);
	ft_execute(head, node);
}

void	process(t_head *head, t_btree *node)
{
	int		fd[2];
	pid_t	pid;

	if (head->n_cmds == 1 && is_parent_builtin(head, node) == 0)
		return ;
	if (head->n_cmds > 1 && head->index < (head->n_cmds -1))
		head->pipe.flag = 1;
	else
		head->pipe.flag = 0;
	if (head->pipe.flag == 1)
	{
		if (pipe(fd) == -1)
			close_fd(fd);
	}
	pid = fork();
	if (pid == -1)
		close_fd(fd);
	if (pid == 0)
		child_process(head, node, fd);
	else
		parent_process(head, node, fd);
	head->pid[head->index] = pid;
	node = NULL;
	head->index++;
}

void	ft_execute(t_head *head, t_btree *node)
{
	if (node->cmd->args)
	{
		if (is_strmatch(node->cmd->path, "built-in"))
			call_builtin(head, node);
		if (node->cmd->path)
		{
			if (execve(node->cmd->path, node->cmd->args, head->env.vars) == -1)
				define_exit_code(errno, TRUE);
		}
	}
	free_btree(head->root);
	free_head(head);
	exit(define_exit_code(0, TRUE));
}
