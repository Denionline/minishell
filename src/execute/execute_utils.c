
#include "minishell.h"

int	count_cmds(t_btree *node, int j)
{
	static int i;

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

void	fd_organizer(t_head *head, t_btree *node, int *fd)
{
	(void)fd;
	if (head->n_cmds == 1 && node->files.in.exists == 0)
		node->files.in.fd = STDIN_FILENO;
	else if (node->files.in.exists == 1)
	{
		node->files.in.fd = open(node->files.in.name, node->files.in.flags);
		dup2(node->files.in.fd, STDIN_FILENO);
		close(node->files.in.fd);
	}
/*	else if (head->index == 0)
		node->fd.in = STDIN_FILENO;*/
	if (head->index == (head->n_cmds - 1))
		node->files.out.fd = STDOUT_FILENO;
	else if (node->files.out.exists == 1)
	{
		node->files.out.fd = open(node->files.out.name, node->files.out.flags, 0644);
		dup2(node->files.out.fd, STDOUT_FILENO);
		close(node->files.out.fd);
	}
}
