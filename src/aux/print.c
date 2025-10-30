
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

static void	print_redirs(t_files files)
{
	if (files.in[0].exists) {
		printf(" (in) associated [");
		for (int i = 0; files.in[i].exists; i++) {
			printf("%s", files.in[i].name);
			if (files.in[i + 1].exists)
				printf(" ,");
		}
		printf("] ");
	}
	if (files.out[0].exists) {
		printf(" (out) associated [");
		for (int i = 0; files.out[i].exists; i++) {
			printf("%s", files.out[i].name);
			if (files.out[i + 1].exists)
				printf(" ,");
		}
		printf("] ");
	}
}

static void	print_command(t_btree *node)
{
	printf("path: %s and args:", node->cmd->path);
	for (int i = 0; node->cmd->args[i]; i++) {
		printf(" arg[%d]: %s", i, node->cmd->args[i]);
	}
	print_redirs(node->files);
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
