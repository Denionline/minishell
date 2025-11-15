#include "minishell.h"

void	ft_error_file(t_head *head, t_btree *node, int *fd, int error)
{
	if (error == 1 && access(node->files.out.name, W_OK) == -1)
	{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(node->files.out.name, 2);
			ft_putendl_fd(": Permission denied", 2);
	}
	else if (error == 0)
	{
		if (access(node->files.in.name, F_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(node->files.in.name, 2);
			ft_putendl_fd(": No such file or directory", 2);
		}
		else if (access(node->files.in.name, R_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(node->files.in.name, 2);
			ft_putendl_fd(": Permission denied", 2);
		}
	}
	free_error(head, node, fd);
	exit(define_exit_code(1, TRUE));
}

void	ft_error_command(t_head *head, t_btree *node, int *fd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(node->cmd->args[0], 2);
	ft_putendl_fd(": command not found", 2);
	free_error(head, node, fd);
	exit(define_exit_code(127, TRUE));
}
void	ft_error_directory(t_head *head, t_btree *node, int *fd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(node->cmd->args[0], 2);
	ft_putendl_fd(": Is a directory", 2);
	free_error(head, node, fd);
	exit(define_exit_code(126, TRUE));
}

void	ft_error_permission(t_head *head, t_btree *node, int *fd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(node->cmd->args[0], 2);
	ft_putendl_fd(": Permission denied", 2);
	free_error(head, node, fd);
	exit(define_exit_code(126, TRUE));
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
	(void)*head;
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": not a valid identifier", 2);
	define_exit_code(1, TRUE);
}

void	ft_syntax_error(t_head *head, int error)
{
	(void)*head;
	if (error == 5)
		ft_putendl_fd("minishell: syntax error near unexpected token", 2);
	else if (error == 6)
		ft_putendl_fd("minishell: quotes unclosed", 2);
	define_exit_code(2, TRUE);
}

void	ft_error_args(t_btree *node)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(node->cmd->args[0], 2);
	ft_putendl_fd(": too many arguments", 2);
	define_exit_code(1, TRUE);
}

void	ft_error_no_cd(t_btree *node)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(node->cmd->args[1], 2);
	ft_putendl_fd(": No such file or directory", 2);
	define_exit_code(1, TRUE);
}

void	ft_error_home_oldpwd(t_head *head)
{
	if (get_var_path("HOME", head->env.vars) == NULL)
		ft_putendl_fd("minishell: cd: HOME not set", 2);
	else if (get_var_path("OLDPWD",  head->env.vars) == NULL)
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
	define_exit_code(1, TRUE);
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
	else if (error == 3)
	 	ft_error_no_cd(node);
	else if (error == 4)
		ft_error_args(node);
	else if (error == 5 || error == 6)
		ft_syntax_error(head, error);
	else if (error == 126)
		ft_error_directory(head, node, fd);
	else if (error == 7)
		ft_error_not_found(head, node, fd);
	else if (error == 8)
		ft_error_home_oldpwd(head);
}
