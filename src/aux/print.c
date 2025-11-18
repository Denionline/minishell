#include "minishell.h"

static void	print_operator(t_btree *node)
{
	if (node->identifier == PIPE)
		printf("|\n");
	else
		printf("(unknown)\n");
}

static void	print_command(t_btree *node)
{
	int	i;

	if (node->cmd->path)
	{
		printf("path: %s and args: ", node->cmd->path);
	}
	if (node->cmd->args)
	{
		i = 0;
		while (node->cmd->args[i])
		{
			printf("arg[%d]: %s ", i, node->cmd->args[i]);
			i++;
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
	if (token->identifier == COMMAND)
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
