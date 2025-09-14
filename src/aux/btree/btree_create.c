
#include "minishell.h"

t_btree	*btree_create(char *identifier, t_cmd *cmd, t_btree *left, t_btree *right)
{
	t_btree	*new_token;

	(void)identifier;
	new_token = ft_calloc(1, sizeof(t_btree));
	if (!new_token)
		return (NULL);
	new_token->identifier = 42;
	new_token->cmd = cmd;
	new_token->left = left;
	new_token->right = right;
	return (new_token);
}
