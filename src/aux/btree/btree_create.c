
#include "minishell.h"

t_btree	*btree_create(int identifier, t_cmd *cmd, t_btree *left, t_btree *right)
{
	t_btree	*new_token;

	new_token = ft_calloc(1, sizeof(t_btree));
	if (!new_token)
		return (NULL);
	new_token = &(t_btree){
		.identifier = identifier,
		.cmd = cmd,
		.left = left,
		.right = right,
		.files = (t_files){
			.in = &(t_file){.fd = -1},
			.out = &(t_file){.fd = -1},
		}
	};
	return (new_token);
}
