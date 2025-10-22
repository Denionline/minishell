
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
	init_pipe(head);
	hierarchy_btree(head, head->root);
	wait_process(head);
	free(head->pid);
	dup2(head->files.in.fd, STDIN_FILENO);
	dup2(head->files.out.fd, STDOUT_FILENO);
}

int	hierarchy_btree(t_head *head, t_btree *node)
{
	if (node == NULL)
		return (0);
	else if (node->identifier == COMMAND)
		organize_process(head, node);
	else if (node->left && node->left->identifier == PIPE)
		hierarchy_btree(head, node->left);
	if (node->left && node->left->identifier == COMMAND)
	{
		organize_process(head, node->left);
		if (node->right->identifier == COMMAND)
			organize_process(head, node->right);
		node = NULL;
	}
	if (node && node->right && node->right->identifier == COMMAND)
		organize_process(head, node->right);
	return (head->exit_code);
}

void	organize_process(t_head *head, t_btree *node)
{
	head->pid[head->index] = child_process(head, node);
	node = NULL;
	head->index++;
}

void	fd_organizer(t_head *head, t_btree *node)
{
//	if (head->n_cmds == 1 && !node->files.in.exists)
//		node->files.in.fd = STDIN_FILENO;
	if (node->files.in.exists == 1)
		node->files.in.fd = open(node->files.in.name, node->files.in.flags);
//	if (head->index == (head->n_cmds - 1) && !node->files.out.exists)
//		node->files.out.fd = STDOUT_FILENO;
	if (node->files.out.exists == 1)
		node->files.out.fd = open(node->files.out.name,
				node->files.out.flags, 0644);
	if (head->n_cmds > 1 && head->index < (head->n_cmds -1))
		head->pipe.flag = 1;
	else
		head->pipe.flag = 0;
}

static void	parent_process(t_head *head, t_btree *node, int *fd)
{
	(void)*node;
	if (head->pipe.pipe_fd[0] != -1)
	{
		close(head->pipe.pipe_fd[0]);
		head->pipe.pipe_fd[0] = -1;
	}
	if (head->pipe.pipe_fd[1] != -1)
	{
		close(head->pipe.pipe_fd[1]);
		head->pipe.pipe_fd[1] = -1;
	}
	if (head->pipe.flag == 1)
	{
		head->pipe.pipe_fd[0] = fd[0];
		head->pipe.pipe_fd[1] = fd[1];
		close(fd[1]);
	}
	else
	{
		head->pipe.pipe_fd[0] = -1;
		head->pipe.pipe_fd[1] = -1;
	}
}

pid_t	child_process(t_head *head, t_btree *node)
{
	int	fd[2];
	pid_t	pid;

	fd_organizer(head, node);
	if (head->pipe.flag == 1)
	{
		if (pipe(fd) == -1)
			close_fd(fd);
	}
	pid = fork();
	if (pid == -1)
		close_fd(fd);
	if (pid == 0)
	{
		if (node->files.in.exists)
		{
			dup2(node->files.in.fd, STDIN_FILENO);
			close(node->files.in.fd);
		}
		else if (head->pipe.pipe_fd[0] != -1)
			dup2(head->pipe.pipe_fd[0], STDIN_FILENO);
		if (node->files.out.exists)
		{
			dup2(node->files.out.fd, STDOUT_FILENO);
			close(node->files.out.fd);
		}
		else if (head->pipe.flag == 1)
		{
			dup2(fd[1], STDOUT_FILENO);
			close_fd(fd);
		}
		if (head->pipe.pipe_fd[0] != -1)
			close(head->pipe.pipe_fd[0]);
		if (head->pipe.pipe_fd[1] != -1)
			close(head->pipe.pipe_fd[1]);
		ft_execute(head, node);
	}
	else
		parent_process(head, node, fd);
	return (pid);
}

void	ft_execute(t_head *head, t_btree *node)
{
	if (is_builtin(node))
		call_builtin(head, node);
	else if (execve(node->cmd->path, node->cmd->args, head->envp) == -1)
		free_node(node);
}

int	wait_process(t_head *head)
{
	int	status;
	int	i = 0;

//	signal_handler();
	while (i < head->n_cmds)
	{
		waitpid(head->pid[i], &status, 0);
		if (WIFEXITED(status))
			head->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			head->exit_code = WTERMSIG(status) + 128;
		i++;
	}
	return (head->exit_code);
}
