
#include "minishell.h"

void	btree_set_file_last_left(t_btree **root, t_files files)
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
