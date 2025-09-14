
#include "minishell.h"

int	hierarchy_btree(t_head *head, t_btree *node)
{
	int	status;

	if (node == NULL)
		return (1);
	else if (node->identifier == COMMAND)
		execute(head, node);
	else if (node->identifier == PIPE)
	{	
		if (node->left->identifier == COMMAND)
			execute_with_pipe(head, node);
		else
			hierarchy_btree(head, node->left);
	}
	else if (node->identifier == AND)
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
	}
	return (0);
}

void	execute_with_pipe(t_head *head, t_btree *node)
{
	if (node->left->identifier == COMMAND)
		execute(head, node->left);
	if (node->right->identifier == COMMAND)
		execute(head, node->right);
}

int	execute(t_head *head, t_btree *node)
{
	pid_t	pid;
	int	status;
	int	exit_code;

	exit_code = 0;
	pid = child_process(head, node);
	waitpid(pid, &status, 0);
	free_all(NULL, node, pid, NULL);
	if (WIFEXITED(status))
		exit_code = (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))	
		exit_code = WTERMSIG(status) + 128;
	head->exit_code = exit_code;
	return (exit_code);
}

pid_t	child_process(t_head *head, t_btree *node)
{
	int	fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		close_fd(fd);
	pid = fork();
	if (pid == -1)
		free_all(NULL, NULL, pid, fd);
	else if (pid == 0)
	{
		if (node->fd.out != -1)
			dup2(node->fd.out, STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
		close_fd(fd);
		if (execve(node->cmd->path, node->cmd->args, head->envp) == -1)
			free_all(NULL, node, pid, NULL);
	}
	else
	{
		if (node->fd.in != -1)
			dup2(node->fd.in, STDIN_FILENO);
		else
			dup2(fd[0], STDIN_FILENO);
		close_fd(fd);
	}
	return (pid);
}
