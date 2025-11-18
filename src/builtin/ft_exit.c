#include "minishell.h"

int	confirm_llong(char *number)
{
	if (n == LLONG_MAX)
	{
		if (!ft_strncmp(number, "9223372036854775807", 19) || !ft_strncmp(number, "+9223372036854775807", 20))
			return (TRUE);
		else if (!ft_strncmp(number, "-9223372036854775808", 20))
			return (TRUE);
		else
			return (FALSE);
	}
}

int	ft_exit_number(t_btree *node)
{
	int	n;

	if (ft_isalpha(node->cmd->args[1][0]) == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(node->cmd->args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (define_exit_code(2, TRUE));
	}
	else
	{
		n = ft_atoll(node->cmd->args[1]);
		if ((n == LLONG_MAX || n = LLONG_MIN) && confirm_llong(node->cmd->args[1]))
			
		if (n > 255)
			n = n % 256;
		else if (n < 0)
			n = 256 + (n % 256);
	}
	return (n);
}

int	ft_args_error(t_head *head, t_btree *node)
{
	if (node->cmd->args[2])
	{
		ft_error(head, (t_error){.id = ERR_TOO_MANY_ARGS, .node = node});
		define_exit_code(1, TRUE);
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
	exit(define_exit_code(exit_status, TRUE));
}
