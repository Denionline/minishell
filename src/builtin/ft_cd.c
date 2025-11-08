
#include "minishell.h"

int	ft_cd(t_head *head, t_btree *node)
{
	if (node->cmd->args[2])
	{
		ft_error(head, node, NULL, 4);
		head->exit_code = 1;
	}
	if (chdir(node->cmd->args[1]) == -1)
	{
		write(2, "minishell: No such file or directory: cd: ", 42);
		ft_putendl_fd(node->cmd->args[1], 2);
		head->exit_code = 1;
	}
	return (0);
}
