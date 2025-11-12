#include "minishell.h"

void	ft_error_file(t_head *head, t_btree *node, int *fd, int error)
{
	if (error == 1 && access(node->files.out.name, W_OK) == -1)
	{
		ft_putstr_fd("minishell: Permission denied: ", 2);
		ft_putendl_fd(node->files.out.name, 2);
	}
	else if (error == 0)
	{
		if (access(node->files.in.name, F_OK) == -1)
			ft_putstr_fd("minishell: No such file or directory: ", 2);
		else if (access(node->files.in.name, R_OK) == -1)
			ft_putstr_fd("minishell: Permission denied: ", 2);
		ft_putendl_fd(node->files.in.name, 2);
	}
	free_error(head, node, fd);
	exit(1);
}

void	ft_error_command(t_head *head, t_btree *node, int *fd)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(node->cmd->args[0], 2);
	free_error(head, node, fd);
	exit(127);
}
void	ft_error_directory(t_head *head, t_btree *node, int *fd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(node->cmd->args[0], 2);
	ft_putendl_fd(": Is a directory", 2);
	free_error(head, node, fd);
	exit(126);
}

void	ft_error_permission(t_head *head, t_btree *node, int *fd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(node->cmd->args[0], 2);
	ft_putendl_fd(": Permission denied", 2);
	free_error(head, node, fd);
	exit(126);
}

void	ft_error_not_found(t_head *head, t_btree *node, int *fd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(node->cmd->args[0], 2);
	ft_putendl_fd(": No such file or directory", 2);
	free_error(head, node, fd);
	exit(127);
}

void	ft_error_export(t_head *head, char *arg)
{
	ft_putstr_fd("minishell: not a valid identifier: export: ", 2);
	ft_putendl_fd(arg, 2);
	head->exit_code = 1;
}

void	ft_syntax_error(t_head *head, int error)
{
	if (error == 5)
		ft_putendl_fd("minishell: syntax error near unexpected token", 2);
	else if (error == 6)
		ft_putendl_fd("minishell: quotes unclosed", 2);
	head->exit_code = 2;
}

void	ft_error_args(t_btree *node)
{
	ft_putstr_fd("minishell: too many arguments: ", 2);
	ft_putendl_fd(node->cmd->args[0], 2);
}

void	ft_error(t_head *head, t_btree *node, int *fd, int error)
{
	(void)*fd;
	if (error == 0 || error == 1)
		ft_error_file(head, node, fd, error);
	else if (error == 2)
		ft_error_command(head, node, fd);
	else if (error == 10)
		ft_error_permission(head, node, fd);
	// else if (error == 3)
	// 	ft_error_export(head, node);
	else if (error == 4)
		ft_error_args(node);
	else if (error == 5 || error == 6)
		ft_syntax_error(head, error);
	else if (error == 126)
		ft_error_directory(head, node, fd);
	else if (error == 7)
		ft_error_not_found(head, node, fd);
}
