
#include "minishell.h"

int	ft_exit_number(t_btree *node)
{
	int	n;

	if (ft_isalpha(node->cmd->args[1][0]) == 1)
	{
		write(2, "minishell: numeric argument required: exit: ", 44);
		ft_putendl_fd(node->cmd->args[1], 2);
		return (2);
	}
	else
	{
		n = ft_atoi(node->cmd->args[1]);
		if (n > 255)
			n = n % 256;
		else if (n < 0)
			n = 256 + (n % 256);
	}
	return (n);
}

int		ft_args_error(t_head *head, t_btree *node)
{
	if (node->cmd->args[2])
	{
		ft_error(NULL, node, NULL, 4);
		head->exit_code = 1;
		return (1);
	}
	return (0);
}

int	ft_exit(t_head *head, t_btree *node)
{
	int	exit_status;

	exit_status = 0;
	ft_putendl_fd("exit", 1);
	if (node)
	{
		if (node->cmd->args[1])
		{
			exit_status = ft_exit_number(node);
			if (ft_args_error(head, node) == 1)
				return (0);
		}
		close_all(head, node, NULL);
		free_node(node);
	}
	close(head->files.in.fd);
	close(head->files.out.fd);
	free_db_str(head->env.vars);
	free(head);
	exit(exit_status);
}
