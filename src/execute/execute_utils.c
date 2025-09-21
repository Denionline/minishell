
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
	if (head->n_cmds == 1)
	{
		node->fd.in = STDIN_FILENO;
		node->fd.out = STDOUT_FILENO;
	}
// se usa isso, o terminal fica aberto e nunca sai	
//	else if (head->index == 0)
//		node->fd.in = STDIN_FILENO;
	else if (head->index == (head->n_cmds - 1))
		node->fd.out = STDOUT_FILENO;
}
