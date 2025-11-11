#include "minishell.h"

void	ft_error_file(t_head *head, t_btree *node, int *fd, int error)
{
	if (error == 1 && access(node->files.out.name, W_OK) == -1)
	{
		write(2, "minishell: Permission denied: ", 30);
		ft_putendl_fd(node->files.out.name, 2);
	}
	else if (error == 0)
	{
		if (access(node->files.in.name, F_OK) == -1)
			write(2, "minishell: No such file or directory: ", 38);
		else if (access(node->files.in.name, R_OK) == -1)
			write(2, "minishell: Permission denied: ", 30);
		ft_putendl_fd(node->files.in.name, 2);
	}
	free_error(head, node, fd);
	exit(1);
}

void	ft_error_command(t_head *head, t_btree *node, int *fd)
{
	write(2, "minishell: command not found: ", 30);
	ft_putendl_fd(node->cmd->args[0], 2);
	free_error(head, node, fd);
	exit(127);
}

void	ft_error_export(t_head *head, t_btree *node)
{
	write(2, "minishell: not a valid identifier: export: ", 44);
	ft_putendl_fd(node->cmd->args[1], 2);
	head->exit_code = 1;
}

void	ft_syntax_error(t_head *head, int error)
{
	if (error == 5)
		write(2, "minishell: syntax error near unexpected token\n", 46);
	else if (error == 6)
		write(2, "minishell: quotes unclosed\n", 27);
	head->exit_code = 2;
	reset_prompt();
}

void	ft_error_args(t_btree *node)
{
	write(2, "minishell: too many arguments: ", 31);
	ft_putendl_fd(node->cmd->args[0], 2);
}

void	ft_error(t_head *head, t_btree *node, int *fd, int error)
{
	(void)*fd;
	if (error == 0 || error == 1)
		ft_error_file(head, node, fd, error);
	else if (error == 2)
		ft_error_command(head, node, fd);
	else if (error == 3)
		ft_error_export(head, node);
	else if (error == 4)
		ft_error_args(node);
	else if (error == 5 || error == 6)
		ft_syntax_error(head, error);
}
