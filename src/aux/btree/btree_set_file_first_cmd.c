
#include "minishell.h"

void	btree_set_file_first_cmd(t_btree **root, t_files files)
{
	t_btree	*temp;

	if (*root)
	{
		temp = *root;
		while (temp->left)
			temp = temp->left;
		temp->files = files;
	}
}
