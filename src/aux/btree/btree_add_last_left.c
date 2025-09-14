
#include "minishell.h"

void	btree_add_last_left(t_token **root, t_token *new_token)
{
	t_token	*temp;

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
