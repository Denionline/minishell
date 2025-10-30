
#include "minishell.h"

void	ft_error_file(t_btree *node, int error)
{
	if (error == 1 && access(node->files.out.name, W_OK) == -1)
	{
		write(2, "minishell: Permission denied: ", 30);
		ft_putstr_fd(node->files.in.name, 2);
	}
	else if (error == 0 && access(node->files.in.name, F_OK) == -1)
	{
		write(2, "minishell: No such file or directory: ", 38);
		ft_putstr_fd(node->files.in.name, 2);
	}
	else if (error == 0 && access(node->files.in.name, R_OK) == -1)
	{
		write(2, "minishell: Permission denied: ", 30);
		ft_putstr_fd(node->files.in.name, 2);
	}
	write(2, "\n", 1);
	exit(1);
}

void	ft_error_command(t_btree *node)
{
	write(2, "minishell: command not found: ", 30);
	ft_putstr_fd(node->cmd->args[0], 2);
	write(2, "\n", 1);
	exit(127);
}

void	ft_error(t_head *head, t_btree *node, int *fd, int error)
{
	close_all(head, node, fd);
	if (error == 0 || error == 1)
		ft_error_file(node, error);
	else if (error == 2)
		ft_error_command(node);
}

