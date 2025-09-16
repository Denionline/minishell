
#include "minishell.h"

static void	print_operator(t_btree *node)
{
	if (node->identifier == AND)
		printf("&&\n");
	else if (node->identifier == OR)
		printf("||\n");
	else if (node->identifier == PIPE)
		printf("|\n");
	else if (node->identifier == ARROW_LEFT)
		printf("< fd=[%d]\n", node->fd.in);
	else if (node->identifier == DOUBLE_ARROW_LEFT)
		printf("<<\n");
	else if (node->identifier == ARROW_RIGHT)
		printf("> fd=[%d]\n", node->fd.out);
	else if (node->identifier == DOUBLE_ARROW_RIGHT)
		printf(">> fd=[%d]\n", node->fd.out);
	else
		printf("(unknown)\n");
}

static void	print_command(t_cmd *cmd)
{
	printf("path: %s and args:", cmd->path);
	for (int i = 0; cmd->args[i]; i++) {
		printf(" arg[%d]: %s", i, cmd->args[i]);
	}
	printf("\n");
}

void	print(t_btree *token)
{
	if (token->left)
		print(token->left);
	if (token->identifier == COMMAND)
		print_command(token->cmd);
	else
		print_operator(token);
	if (token->right)
		print(token->right);
}
