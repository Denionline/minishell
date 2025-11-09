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
	if (node->identifier == EMPTY)
		printf("(empty node)");
	if (node->cmd->path)
	{
		printf("path: %s and args: ", node->cmd->path);
	}
	if (node->cmd->args)
	{
		for (int i = 0; node->cmd->args[i]; i++)
		{
			printf("arg[%d]: %s ", i, node->cmd->args[i]);
		}
	}
	if (node->files.out.exists)
		printf("(out)[%s]", node->files.out.name);
	if (node->files.in.exists)
		printf("(in)[%s]", node->files.in.name);
	printf("\n");
}

static void	run_tree(t_btree *token)
{
	if (!token)
		return ;
	if (token->left)
		run_tree(token->left);
	if (token->identifier == COMMAND || token->identifier == EMPTY)
		print_command(token);
	else
		print_operator(token);
	if (token->right)
		run_tree(token->right);
}

void	print(t_head *head)
{
	run_tree(head->root);
	head->root = NULL;
}
