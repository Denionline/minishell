
#include "minishell.h"

int	is_builtin(t_btree *node)
{
	if (ft_strncmp(node->cmd->args[0], "pwd",
			ft_strlen(node->cmd->args[0])) == 0)
		return (0);
	else if (ft_strncmp(node->cmd->args[0], "cd",
			ft_strlen(node->cmd->args[0])) == 0)
		return (0);
	return (1);
}

void	call_builtin(t_btree *node)
{
	if (ft_strncmp(node->cmd->args[0], "pwd",
			ft_strlen(node->cmd->args[0])) == 0)
		ft_pwd(node);
	else if (ft_strncmp(node->cmd->args[0], "cd",
			ft_strlen(node->cmd->args[0])) == 0)
		ft_cd(node->cmd->args[1]);
}
