
#include "minishell.h"

void	ft_exit(t_head *head, t_btree *node)
{

	ft_putendl_fd("exit", 1);
	if (node)
	{
		close_all(head, node, NULL);
		free_node(node);
	}
	close(head->files.in.fd);
	close(head->files.out.fd);
	// if (head->root)
	// 	free_btree(head->root);
	free_db_str(head->env.vars);
	free(head);
	exit (0);
}
