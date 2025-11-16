#include "minishell.h"

static void	print_error(char *prearg, char *arg, char *error_msg)
{
	if (!error_msg)
		return ;
	ft_putstr_fd("minishell: ", 2);
	if (prearg)
	{
		ft_putstr_fd(prearg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd("\n", 2);
}

// static handle_error(t_head *head, t_btree *node, int *fd)
// {

// }

void	ft_error_file(t_head *head, t_btree *node, int *fd, int error)
{
	if (error == 1 && access(node->files.out.name, W_OK) == -1)
		print_error(NULL, node->files.out.name, "Permission denied");
	else if (error == 0)
	{
		if (access(node->files.in.name, F_OK) == -1)
			print_error(NULL, node->files.in.name, "No such file or directory");
		else if (access(node->files.in.name, R_OK) == -1)
			print_error(NULL, node->files.in.name, "Permission denied");
	}
	free_error(head, node, fd);
	exit(define_exit_code(1, TRUE));
}

void	ft_error_command(t_head *head, t_btree *node, int *fd)
{
	print_error(NULL, node->cmd->args[0], "command not found");
	free_error(head, node, fd);
	exit(define_exit_code(127, TRUE));
}
void	ft_error_directory(t_head *head, t_btree *node, int *fd)
{
	print_error(NULL, node->cmd->args[0], "Is a directory");
	free_error(head, node, fd);
	exit(define_exit_code(126, TRUE));
}

void	ft_error_permission(t_head *head, t_btree *node, int *fd)
{
	print_error(NULL, node->cmd->args[0], "Permission denied");
	free_error(head, node, fd);
	exit(define_exit_code(126, TRUE));
}

void	ft_error_not_found(t_head *head, t_btree *node, int *fd)
{
	print_error(NULL, node->cmd->args[0], "No such file or directory");
	free_error(head, node, fd);
	exit(define_exit_code(127, TRUE));
}

void	ft_error_export(t_head *head, char *arg)
{
	(void)*head;
	print_error("export", arg, "not a valid identifier");
	define_exit_code(1, TRUE);
}

void	ft_syntax_error(t_head *head, int error)
{
	(void)*head;
	if (error == 5)
		print_error(NULL, NULL, "syntax error near unexpected token");
	else if (error == 6)
		print_error(NULL, NULL, "quotes unclosed");
	define_exit_code(2, TRUE);
}

void	ft_error_args(void)
{
	print_error("cd", NULL, "too many arguments");
	define_exit_code(1, TRUE);
}

void	ft_error_no_cd(t_btree *node)
{
	if (access(node->cmd->args[1], F_OK) == -1)
		print_error("cd", node->cmd->args[1], "No such file or directory");
	else
		print_error("cd", node->cmd->args[1], "Not a directory");
	define_exit_code(1, TRUE);
}

void	ft_error_home_oldpwd(t_head *head, t_btree *node)
{
	if (node->cmd->args[1] == NULL && get_var_path("HOME", head->env.vars) == NULL)
		print_error("cd", NULL, "HOME not set");
	else if (get_var_path("OLDPWD",  head->env.vars) == NULL)
		print_error("cd", NULL, "OLDPWD not set");
	define_exit_code(1, TRUE);
}

void	ft_error(t_head *head, t_btree *node, int *fd, int error)
{
	if (error == 0 || error == 1)
		ft_error_file(head, node, fd, error);
	else if (error == 2)
		ft_error_command(head, node, fd);
	else if (error == 10)
		ft_error_permission(head, node, fd);
	else if (error == 3)
	 	ft_error_no_cd(node);
	else if (error == 4)
		ft_error_args();
	else if (error == 5 || error == 6)
		ft_syntax_error(head, error);
	else if (error == 126)
		ft_error_directory(head, node, fd);
	else if (error == 7)
		ft_error_not_found(head, node, fd);
	else if (error == 8)
		ft_error_home_oldpwd(head, node);
}
