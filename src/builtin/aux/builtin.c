
#include "minishell.h"

int	is_builtin(char *command)
{
	if (!ft_strncmp("exit", command, ft_strlen("exit")))
		return (TRUE);
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
		ft_pwd(node);
	if (!ft_strncmp("env", command, ft_strlen("env")))
		ft_env(head->env.vars, FALSE);
	if (!ft_strncmp("echo", command, ft_strlen("echo")))
		ft_echo(node->cmd);
	free_node(node);
	free_head(head);
	exit(0);
}

int	is_parent_builtin(t_head *head, t_btree *node)
{
	char	*command;

	if (!node->cmd->args)
		return (1);
	command = node->cmd->args[0];
	if (!ft_strncmp("exit", command, ft_strlen("exit")) && head->n_cmds == 1)
	{
		ft_exit(head, node);
		return (0);
	}
	if (!ft_strncmp("cd", command, ft_strlen("cd")))
	{
		ft_cd(node->cmd->args[1]);
		return (0);
	}
	if (!ft_strncmp("export", command, ft_strlen("export")))
	{
		ft_export(node->cmd, &head->env);
		return (0);
	}
	if (!ft_strncmp("unset", command, ft_strlen("unset")))
	{
		ft_unset(node->cmd, &head->env);
		return (0);
	}
	//add unset 
	//add exit?
	return (1);
}
