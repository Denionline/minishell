
#include "minishell.h"

int	count_cmds(t_btree *node, int j)
{
	static int	i;

	if (!node)
		return (0);
	i = j;
	if (node->identifier == COMMAND)
		i += 1;
	else if (node->identifier != COMMAND)
	{
		if (node->left)
			count_cmds(node->left, i);
		if (node->right)
			count_cmds(node->right, i);
	}
	return (i);
}

void	reset_head(t_head *head)
{
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

void	close_all(t_head *head, t_btree *node, int *fd)
{
	dup2(head->files.in.fd, STDIN_FILENO);
	dup2(head->files.out.fd, STDOUT_FILENO);
	free(head->pid);
	if (head->pipe.flag == 1)
		close_fd(fd);
	close_all_fds(head, node, 0);
}
