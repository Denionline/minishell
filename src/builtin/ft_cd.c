#include "minishell.h"

int	ft_cd(t_head *head, t_btree *node)
{
	if (node->cmd->args[2])
	{
		ft_error(head, node, NULL, 4);
		define_exit_code(1, TRUE);
	}
	else if (chdir(node->cmd->args[1]) == -1)
	{
		write(2, "minishell: No such file or directory: cd: ", 42);
		ft_putendl_fd(node->cmd->args[1], 2);
		define_exit_code(1, TRUE);
	}
	return (0);
}
