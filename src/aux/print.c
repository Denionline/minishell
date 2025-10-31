
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

static void	print_redirs(t_files *files)
{
	if (files->in[0].exists) {
		ft_putstr_fd(" (in) associated [", 1);
		for (int i = 0; files->in[i].exists; i++) {
			ft_putstr_fd(files->in[i].name, 1);
			if (files->in[i + 1].exists)
				ft_putstr_fd(" ,", 1);
		}
		ft_putstr_fd("] ", 1);
	}
	if (files->out[0].exists) {
		ft_putstr_fd(" (out) associated [", 1);
		for (int i = 0; files->out[i].exists; i++) {
			ft_putstr_fd(files->out[i].name, 1);
			if (files->out[i + 1].exists)
				ft_putstr_fd(" ,", 1);
		}
		ft_putstr_fd("] ", 1);
	}
}

static void	print_command(t_btree *node)
{
	ft_putstr_fd("path: ", 1);
	ft_putstr_fd(node->cmd->path, 1);
	ft_putstr_fd(" and args:", 1);
	for (int i = 0; node->cmd->args[i]; i++) {
		ft_putstr_fd(" arg[", 1);
		ft_putnbr_fd(i, 1);
		ft_putstr_fd("]: ", 1);
		ft_putstr_fd(node->cmd->args[i], 1);
	}
	print_redirs(&node->files);
	ft_putstr_fd("\n", 1);
}

void	print(t_btree *token)
{
	if (!token)
		return ;
	if (token->left)
		print(token->left);
	if (token->identifier == COMMAND)
		print_command(token);
	else
		print_operator(token);
	if (token->right)
		print(token->right);
}
