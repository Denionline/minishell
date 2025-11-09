#include "minishell.h"

void	btree_add_as_first(t_btree **root, t_btree *new_node)
{
	if (!(*root))
		(*root) = new_node;
	else
	{
		new_node->left = (*root);
		*root = new_node;
	}
}
