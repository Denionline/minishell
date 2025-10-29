
#include "minishell.h"

void	ft_put_fd(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

void	ft_error_file(t_head *head, t_btree *node, int *fd, int error)
{
	(void)*fd;
	(void)*head;
	if (error == 1 && access(node->files.out.name, W_OK) == -1)
	{
		ft_putstr_fd("minishell: Permission denied: ", 2);
		ft_putstr_fd(node->files.in.name, 2);
	}
	else if (error == 0 && access(node->files.in.name, F_OK) == -1)
	{
		ft_put_fd("minishell: No such file or directory: ", 2);
//		write(2, "minishell: No such file or directory: ", 38);
		ft_put_fd(node->files.in.name, 2);
	}
	else if (error == 0 && access(node->files.in.name, R_OK) == -1)
	{
		ft_putstr_fd("minishell: Permission denied: ", 2);
		ft_putstr_fd(node->files.in.name, 2);
	}
//	write(2, "\n", 1);
	ft_put_fd("\n", 2);
	exit(1);
}

void	ft_error_command(t_head *head, t_btree *node, int *fd)
{
	(void)*fd;
	(void)*head;
	(void)*node;
	ft_put_fd("minishell: command not found: ", 2);
//	write(2, "minishell: command not found: ", 30);
	ft_put_fd(node->cmd->args[0], 2);
//	write(2, "\n", 1);
	ft_putstr_fd("\n", 2);
	exit(127);
}

void	ft_error(t_head *head, t_btree *node, int *fd, int error)
{
	dup2(head->files.in.fd, STDIN_FILENO);
        dup2(head->files.out.fd, STDOUT_FILENO);
	free(head->pid);
	if (head->pipe.flag == 1)
		close_fd(fd);
	close_all_fds(head, node, 0);
	if (error == 0 || error == 1)
		ft_error_file(head, node, fd, error);
	else if (error == 2)
		ft_error_command(head, node, fd);
}

