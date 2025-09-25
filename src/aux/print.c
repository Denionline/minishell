
#include "minishell.h"

static void	print_operator(t_btree *node)
{
	if (node->identifier == AND)
		printf("&&\n");
	else if (node->identifier == OR)
		printf("||\n");
	else if (node->identifier == PIPE)
		printf("|\n");
	else
		printf("(unknown)\n");
}

static void	print_command(t_btree *node)
{
	printf("path: %s and args:", node->cmd->path);
	for (int i = 0; node->cmd->args[i]; i++) {
		printf(" arg[%d]: %s", i, node->cmd->args[i]);
	}
	if (node->files.out.exists)
		printf(" (out) associated [%s]", node->files.out.name);
	else if (node->files.in.exists)
		printf(" (in) associated [%s]", node->files.in.name);
	printf("\n");
}

void	print(t_btree *token)
{
	if (token->left)
		print(token->left);
	if (token->identifier == COMMAND)
		print_command(token);
	else
		print_operator(token);
	if (token->right)
		print(token->right);
}
