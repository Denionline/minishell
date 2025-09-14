
#include "minishell.h"

void	btree_add_last_left(t_btree **root, t_btree *new_token)
{
	t_btree	*temp;

	if (!(*root))
		(*root) = new_token;
	else
	{
		temp = *root;
		while (temp->left)
			temp = temp->left;
		temp->left = new_token;
	}
}
