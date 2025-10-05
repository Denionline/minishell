
#include "minishell.h"

int	is_builtin(t_btree *node)
{
	if (ft_strncmp(node->cmd->args[0], "pwd", ft_strlen(node->cmd->args[0])) == 0)
		return (0);
	return (1);
}

void	call_builtin(t_btree *node)
{
	ft_pwd(node);
}
