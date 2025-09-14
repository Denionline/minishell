
#include "minishell.h"

void	btree_add_last_right(t_token **root, t_token *new_token)
{
	t_token	*temp;

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
