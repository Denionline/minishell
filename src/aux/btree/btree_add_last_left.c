
#include "minishell.h"

void	btree_add_last_left(t_token **root, t_token *new_token)
{
	if (!(*root))
		(*root) = new_token;
	else
	{
		while((*root)->left)
			(*root) = (*root)->left;
		(*root)->left = new_token;
	}
}
