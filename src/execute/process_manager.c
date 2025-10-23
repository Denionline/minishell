
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
	reset_pipe(head);
	hierarchy_btree(head, head->root);
	wait_process(head);
	free(head->pid);
	dup2(head->files.in.fd, STDIN_FILENO);
	dup2(head->files.out.fd, STDOUT_FILENO);
	close_all_fds(head, NULL, 0);
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
	return (head->exit_code);
}

int	wait_process(t_head *head)
{
	int	status;
	int	i;

//	signal_handler();
	i = 0;
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
