
#include "minishell.h"

int	is_builtin(char *command)
{
	if (!ft_strncmp("pwd", command, ft_strlen("pwd")))
		return (TRUE);
	if (!ft_strncmp("cd", command, ft_strlen("cd")))
		return (TRUE);
	if (!ft_strncmp("env", command, ft_strlen("env")))
		return (TRUE);
	if (!ft_strncmp("export", command, ft_strlen("export")))
		return (TRUE);
	if (!ft_strncmp("unset", command, ft_strlen("unset")))
		return (TRUE);
	if (!ft_strncmp("echo", command, ft_strlen("echo")))
		return (TRUE);
	return (FALSE);
}

void	call_builtin(t_head *head, t_btree *node)
{
	const char	*command = node->cmd->args[0];

	if (!ft_strncmp("pwd", command, ft_strlen("pwd")))
		exit(ft_pwd(node));
	if (!ft_strncmp("env", command, ft_strlen("env")))
		exit(ft_env(head->env.vars));
	if (!ft_strncmp("echo", command, ft_strlen("echo")))
		exit(ft_echo(node->cmd));
	/*
	if (!ft_strncmp("cd", command, ft_strlen("cd")))
		exit(ft_cd(node->cmd->args[1]));
	if (!ft_strncmp("export", command, ft_strlen("export")))
		exit(ft_export(node->cmd, &head->env));
	*/
}

int	is_parent_builtin(t_head *head, t_btree *node)
{
	if (!ft_strncmp(node->cmd->args[0], "cd", 2))
	{
		ft_cd(node->cmd->args[1]);
		return (0);
	}
	if (!ft_strncmp(node->cmd->args[0], "export", 7))
	{
		ft_export(node->cmd, &head->env);
		return (0);
	}
	if (!ft_strncmp(node->cmd->args[0], "unset", 6))
	{
		ft_unset(node->cmd, &head->env);
		return (0);
	}
	//add unset 
	//add exit?
	return (1);
}
