
#include "minishell.h"

void	redirect(t_head *head, t_btree *node, int *fd)
{
	if (node->files.in.exists)
	{
		node->files.in.fd = open(node->files.in.name, node->files.in.flags);
		if (node->files.in.fd == -1)
			ft_error(head, node, fd, 0);
		dup2(node->files.in.fd, STDIN_FILENO);
		close(node->files.in.fd);
	}
	if (node->files.out.exists)
	{
		node->files.out.fd = open(node->files.out.name,
				node->files.out.flags, 0664);
		if (node->files.out.fd == -1)
			ft_error(head, node, fd, 1);
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
	//free_node(node);
	//free_head(head);
}

void	child_process(t_head *head, t_btree *node, int *fd)
{
	if (node->files.in.exists || node->files.out.exists)
		redirect(head, node, fd);
	if (head->pipe.pipe_fd[0] != -1)
		dup2(head->pipe.pipe_fd[0], STDIN_FILENO);
	if (head->pipe.flag == 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_fd(fd);
	}
	if (!node->cmd->path)
		ft_error(head, node, fd, 2);
	close_all_fds(head, node, 0);
	ft_execute(head, node);
}

void	process(t_head *head, t_btree *node)
{
	int		fd[2];
	pid_t	pid;

	if (is_parent_builtin(head, node) == 0)
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
	if (is_builtin(node->cmd->args[0]))
		call_builtin(head, node);
	else if (execve(node->cmd->path, node->cmd->args, head->env.vars) == -1)
		free_node(node);
}

