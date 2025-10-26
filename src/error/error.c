
#include "minishell.h"

void	ft_error_file(t_head *head, t_btree *node, int *fd, int error)
{
	ft_putstr_fd("minishell: ", 1);
	if (error == 0)
		ft_putstr_fd(node->files.in.name, 1);
	else if (error == 1)
		ft_putstr_fd(node->files.out.name, 1);
	if (error == 0 && access(node->files.in.name, F_OK) == -1)
		ft_putstr_fd(": No such file or directory\n", 1);
	else if (error == 0 && access(node->files.in.name, R_OK) == -1)
		ft_putstr_fd(": Permission denied\n", 1);
	else if (error == 1 && access(node->files.out.name, W_OK) == -1)
		ft_putstr_fd(": Permission denied\n", 1);
	free(head->pid);
	if (head->pipe.flag == 1)
		close_fd(fd);
	dup2(head->files.in.fd, STDIN_FILENO);
        dup2(head->files.out.fd, STDOUT_FILENO);
	close_all_fds(head, node, 0);
	exit(1);
}

void	ft_error_command(t_head *head, t_btree *node, int *fd)
{
	free(head->pid);
	if (head->pipe.flag == 1)
		close_fd(fd);
	dup2(head->files.in.fd, STDIN_FILENO);
        dup2(head->files.out.fd, STDOUT_FILENO);
	close_all_fds(head, node, 0);
	head->exit_code = 127;
	exit(1);
}

void	ft_error(t_head *head, t_btree *node, int *fd, int error)
{
	if (error == 0 || error == 1)
		ft_error_file(head, node, fd, error);
	else if (error == 2)
		ft_error_command(head, node, fd);
}

