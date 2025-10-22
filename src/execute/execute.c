
#include "minishell.h"

void	fd_organizer(t_head *head, t_btree *node)
{
	if (node->files.in.exists == 1)
		node->files.in.fd = open(node->files.in.name, node->files.in.flags);
	if (node->files.out.exists == 1)
		node->files.out.fd = open(node->files.out.name,
				node->files.out.flags, 0644);
	if (head->n_cmds > 1 && head->index < (head->n_cmds -1))
		head->pipe.flag = 1;
	else
		head->pipe.flag = 0;
}

void	parent_process(t_head *head, int *fd)
{
	//in the parent process, reset pipe_fds
	if (head->pipe.pipe_fd[0] != -1)
		close(head->pipe.pipe_fd[0]);
	if (head->pipe.pipe_fd[1] != -1)
		close(head->pipe.pipe_fd[1]);
	if (head->pipe.flag == 1)
	{
		head->pipe.pipe_fd[0] = dup(fd[0]);
		head->pipe.pipe_fd[1] = dup(fd[1]);
		//leave read pipe open for next pipe command
		//close(fd[1]);
		close_fd(fd);
	}
	else if (head->pipe.flag == 0)
	{
		close_fd(fd);
		reset_pipe(head);
	}
}

void	child_process(t_head *head, t_btree *node, int *fd)
{
	if (node->files.in.exists)
	{
		dup2(node->files.in.fd, STDIN_FILENO);
		close(node->files.in.fd);
	}
	//se existe ja a abertura para o pipe, usa ela de entrada pro comando
	else if (head->pipe.pipe_fd[0] != -1)
	{
		dup2(head->pipe.pipe_fd[0], STDIN_FILENO);
		close(head->pipe.pipe_fd[0]);
	}
	if (node->files.out.exists)
	{
		dup2(node->files.out.fd, STDOUT_FILENO);
		close(node->files.out.fd);
	}
	//se existe flag de proximo pipe, usa a saida do pipe
	else if (head->pipe.flag == 1)
	{
		dup2(fd[1], STDOUT_FILENO);
		close_fd(fd);
	}
	if (head->pipe.pipe_fd[1] != -1)
		close(head->pipe.pipe_fd[1]);
	ft_execute(head, node);
}

void	process(t_head *head, t_btree *node)
{
	int		fd[2];
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
		child_process(head, node, fd);
	}
	else
		parent_process(head, fd);
	head->pid[head->index] = pid;
	node = NULL;
	head->index++;
}

void	ft_execute(t_head *head, t_btree *node)
{
	//nao e melhor mandar direto o head e node para call_builtin?
	if (is_builtin(node->cmd->args[0], ft_strlen(node->cmd->args[0])))
		call_builtin(head, node, node->cmd->args[0],
			ft_strlen(node->cmd->args[0]));
	else if (execve(node->cmd->path, node->cmd->args, head->env.vars) == -1)
		free_node(node);
}

