
#include "minishell.h"

void	btree_add_last_right(t_token **root, t_token *new_token)
{
	if ((*root)->right)
		btree_add_last_right(&(*root)->right, new_token);
	if (!(*root)->right)
		(*root)->right = new_token;
}
