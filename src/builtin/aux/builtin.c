
#include "minishell.h"

int	is_builtin(t_btree *node)
{
	const char	*command = node->cmd->args[0];
	const int	lcommand = ft_strlen(command);

	if (!ft_strncmp(command, "pwd", lcommand))
		return (TRUE);
	if (!ft_strncmp(command, "cd", lcommand))
		return (TRUE);
	if (!ft_strncmp(command, "env", lcommand))
		return (TRUE);
	return (FALSE);
}

void	call_builtin(t_head *head, t_btree *node)
{
	const char	*command = node->cmd->args[0];
	const int	lcommand = ft_strlen(command);

	if (!ft_strncmp(command, "pwd", lcommand))
		ft_pwd(node);
	if (!ft_strncmp(command, "cd", lcommand))
		ft_cd(node->cmd->args[1]);
	if (!ft_strncmp(command, "env", lcommand))
		ft_env(head->env.vars);
}
