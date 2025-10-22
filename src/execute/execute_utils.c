
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

void	reset_pipe(t_head *head)
{
	head->pipe.pipe_fd[0] = -1;
	head->pipe.pipe_fd[1] = -1;
}
