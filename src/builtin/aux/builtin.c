
#include "minishell.h"

int	is_builtin(char *command, int lcommand)
{
	if (!ft_strncmp(command, "pwd", lcommand))
		return (TRUE);
	if (!ft_strncmp(command, "cd", lcommand))
		return (TRUE);
	if (!ft_strncmp(command, "env", lcommand))
		return (TRUE);
	if (!ft_strncmp(command, "export", lcommand))
		return (TRUE);
	if (!ft_strncmp(command, "echo", lcommand))
		return (TRUE);
	return (FALSE);
}

void	call_builtin(t_head *head, t_btree *node, char *command, int lcommand)
{
	if (!ft_strncmp(command, "pwd", lcommand))
		exit(ft_pwd(node));
//	if (!ft_strncmp(command, "cd", lcommand))
//		exit(ft_cd(node->cmd->args[1]));
	if (!ft_strncmp(command, "env", lcommand))
		exit(ft_env(head->env.vars));
//	if (!ft_strncmp(command, "export", lcommand))
//		exit(ft_export(node->cmd, &head->env));
	if (!ft_strncmp(command, "echo", lcommand))
		exit(ft_echo(node->cmd));
}

int	is_parent_builtin(t_head *head, t_btree *node)
{
	if (!ft_strncmp(node->cmd->args[0], "cd", 2))
	{
		ft_cd(node->cmd->args[1]);
		return (0);
	}
	if (!ft_strncmp(node->cmd->args[0], "export", 6))
	{
		ft_export(node->cmd, &head->env);
		return (0);
	}
	//add unset 
	//add exit?
	return (1);
}
