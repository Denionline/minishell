#include "minishell.h"

void	btree_add_last_right(t_btree **root, t_btree *new_token)
{
	t_btree	*temp;

	if (!(*root))
		(*root) = new_token;
	else
	{
		temp = *root;
		while (temp->right)
			temp = temp->right;
		temp->right = new_token;
	}
}
