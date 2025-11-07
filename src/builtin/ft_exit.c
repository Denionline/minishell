
#include "minishell.h"

int	ft_exit_number(t_head *head, t_btree *node)
{
	int	n;

	(void)*head;
	n = ft_atoi(node->cmd->args[1]);
	if (n > 255)
		n = n % 256;
	else if (n < 0)
	{
		n = n % 256;
		n = 256 + n;
	}
	return (n);
}

void	ft_exit(t_head *head, t_btree *node)
{
	int	exit_status;

	exit_status = 0;
	ft_putendl_fd("exit", 1);
	if (node)
	{
		if (node->cmd->args[1])
			exit_status = ft_exit_number(head, node);
		close_all(head, node, NULL);
		free_node(node);
	}
	close(head->files.in.fd);
	close(head->files.out.fd);
	free_db_str(head->env.vars);
	free(head);
	exit (exit_status);
}
