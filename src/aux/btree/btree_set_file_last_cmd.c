
#include "minishell.h"

static void	set_or_replace(t_btree **node, t_files files)
{
	if ((*node)->files.in.name)
		free((*node)->files.in.name);
	if ((*node)->files.out.name)
		free((*node)->files.out.name);
	(*node)->files = files;
}

void	btree_set_file_last_cmd(t_btree **root, t_files files)
{
	if (*root)
	{
		if ((*root)->right && (*root)->right->identifier == COMMAND)
			set_or_replace(&(*root)->right, files);
		else if ((*root)->identifier == COMMAND)
			set_or_replace(root, files);
	}
}
