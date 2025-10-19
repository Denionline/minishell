
#include "minishell.h"

void	execute_manager(t_head *head)
{
	head->files.in.fd = dup(STDIN_FILENO);
	head->files.out.fd = dup(STDOUT_FILENO);
	head->n_cmds = count_cmds(head->root, 0);
	head->pid = malloc(sizeof(pid_t) * head->n_cmds);
	if (!head->pid)
		return ;
	head->index = 0;
	hierarchy_btree(head, head->root);
	dup2(head->files.in.fd, STDIN_FILENO);
	dup2(head->files.out.fd, STDOUT_FILENO);
	close(head->files.in.fd);
	close(head->files.out.fd);
	free(head->pid);
}

int	hierarchy_btree(t_head *head, t_btree *node)
{
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
		node = NULL;
	}
	if (node && node->right && node->right->identifier == COMMAND)
		execute(head, node->right);
/*	else if (node && node->identifier == AND)
	{
		head->exit_code = hierarchy_btree(head, node->left);
		if (head->exit_code == 0)
			hierarchy_btree(head, node->right);
	}
	else if (node && node->identifier == OR)
	{
		head->exit_code = hierarchy_btree(head, node->left);
		if (head->exit_code != 0)
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
	node = NULL;
//	free_node(node);
	head->index++;
	return (head->exit_code);
}

void	ft_execute(t_head *head, t_btree *node)
{
//	signal_child();
	if (is_builtin(node)) //isso pode ser uma flag na struct??
		call_builtin(head, node);
	else if (execve(node->cmd->path, node->cmd->args, head->envp) == -1)
		free_node(node);
}

pid_t	child_process(t_head *head, t_btree *node)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		close_fd(fd);
	fd_organizer(head, node, fd);
	pid = fork();
	if (pid == -1)
		close_fd(fd);
	else if (pid == 0)
	{
		close(head->files.in.fd);
		close(head->files.out.fd);
		if (node->files.out.fd == -1)
			dup2(fd[1], STDOUT_FILENO);
		close_fd(fd);
		ft_execute(head, node);
	}
	else
	{
		if (node->files.in.fd == -1)
			dup2(fd[0], STDIN_FILENO);
		close_fd(fd);
	}
	return (pid);
}
