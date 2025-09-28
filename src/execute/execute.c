
#include "minishell.h"

void	execute_manager(t_head *head)
{
	head->fd.in = dup(STDIN_FILENO);
	head->fd.out = dup(STDOUT_FILENO);
	head->n_cmds = count_cmds(head->root, 0);
	head->pid = malloc(sizeof(pid_t) * head->n_cmds);
	if (!head->pid)
		return ;
	head->index = 0;
	hierarchy_btree(head, head->root);
	dup2(head->fd.in, STDIN_FILENO);
	dup2(head->fd.out, STDOUT_FILENO);
}

int	hierarchy_btree(t_head *head, t_btree *node)
{
//	int	status;

	if (node == NULL)
		return (0);
	else if (node->identifier == COMMAND)
		execute(head, node);
	else if (node->left && node->left->identifier == PIPE)
		hierarchy_btree(head, node->left);
	if (node->left && node->left->identifier == COMMAND)
	{
		execute(head, node->left);
		if (node->right->identifier == COMMAND)
			execute(head, node->right);
//		free_node(node);
	}
	if (node->right && node->right->identifier == COMMAND)
	{
		execute(head, node->right);
//		free_node(node->right);
	}
/*	else if (node->identifier == AND)
	{
		status = hierarchy_btree(head, node->left);
		if (status == 0)
			hierarchy_btree(head, node->right);
	}
	else if (node->identifier == OR)
	{
		status = hierarchy_btree(head, node->left);
		if (status != 0)
			hierarchy_btree(head, node->right);
	}*/
	return (head->exit_code);
}

int	execute(t_head *head, t_btree *node)
{
	int	status;

	head->pid[head->index] = child_process(head, node);
	waitpid(head->pid[head->index], &status, 0);
	if (head->index == (head->n_cmds - 1))
	{
		if (WIFEXITED(status))
			head->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			head->exit_code = WTERMSIG(status) + 128;
	}
	free_node(node);
	head->index++;
	return (head->exit_code);
}

pid_t	child_process(t_head *head, t_btree *node)
{
	int	fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		close_fd(fd);
	fd_organizer(head, node, fd);
	pid = fork();
	if (pid == -1)
		close_fd(fd);
	else if (pid == 0)
	{
		if (node->fd.out == -1)
			dup2(fd[1], STDOUT_FILENO);
		close_fd(fd);
		if (execve(node->cmd->path, node->cmd->args, head->envp) == -1)
			free_node(node);
	}
	else
	{
		if (node->fd.in == -1)
			dup2(fd[0], STDIN_FILENO);
		close_fd(fd);
	}
	return (pid);
}

int	wait_list(t_head *head)
{
	int	i;
	int	status;

	i = head->index - 1;
	while (i < head->n_cmds)
	{
		waitpid(head->pid[i], &status, 0);
		if (i == (head->n_cmds -1))
		{
			if (WIFEXITED(status))
				head->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				head->exit_code = WTERMSIG(status) + 128;
		}
		i++;
	}
	return (head->exit_code);
}
