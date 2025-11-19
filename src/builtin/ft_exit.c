#include "minishell.h"

int	is_str_alpha(char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (ft_isalpha(string[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
int	confirm_llong(char *number)
{
	if (!ft_strncmp(number, "9223372036854775807", 19) || 
			!ft_strncmp(number, "+9223372036854775807", 20))
		return (TRUE);
	else if (!ft_strncmp(number, "-9223372036854775808", 20))
		return (TRUE);
	else
		return (FALSE);
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
int	error_num_required(t_btree *node)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(node->cmd->args[1], 2);
	ft_putendl_fd(": numeric argument required", 2);
	return (define_exit_code(2, TRUE));
}

int	ft_exit_number(t_btree *node)
{
	long long	n;

	n = ft_atoll(node->cmd->args[1]);
	if ((n == LLONG_MAX || n == LLONG_MIN) && confirm_llong(node->cmd->args[1]))
		return (n);
	else if (n > 0 && n < 255)
		return (n);
	else if (n < LLONG_MAX && n > 255)
		return (n % 256);
	else if (n > LLONG_MIN && n < 0)
		return (256 + (n % 256));
	else
		return (error_num_required(node));
}

int	ft_exit(t_head *head, t_btree *node)
{
	long long	exit_status;

	exit_status = 0;
	ft_putendl_fd("exit", 1);
	if (node)
	{
		if (node->cmd->args[1])
		{
			if (is_str_alpha(node->cmd->args[1]) == 1)
				exit_status = error_num_required(node);
			else if (ft_args_error(head, node) == 1)
				return (0);
			else
				exit_status = ft_exit_number(node);
			define_exit_code((int)exit_status, TRUE);
		}
		close_all(head, node, NULL);
		free_node(node);
	}
	close(head->files.in.fd);
	close(head->files.out.fd);
	free_db_str(head->env.vars);
	free(head);
	exit(define_exit_code(0, FALSE)); 
}