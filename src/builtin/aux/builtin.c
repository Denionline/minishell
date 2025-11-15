#include "minishell.h"

int	is_builtin(char *command)
{
	const int	size = ft_strlen(command);

	if (!ft_strncmp("exit", command, size))
		return (TRUE);
	if (!ft_strncmp("pwd", command, size))
		return (TRUE);
	if (!ft_strncmp("cd", command, size))
		return (TRUE);
	if (!ft_strncmp("env", command, size))
		return (TRUE);
	if (!ft_strncmp("export", command, size))
		return (TRUE);
	if (!ft_strncmp("unset", command, size))
		return (TRUE);
	if (!ft_strncmp("echo", command, size))
		return (TRUE);
	return (FALSE);
}

void	call_builtin(t_head *head, t_btree *node)
{
	const char	*command = node->cmd->args[0];
	const int	size = ft_strlen(command);

	if (!ft_strncmp("pwd", command, size))
		ft_pwd();
	if (!ft_strncmp("env", command, size))
		ft_env(head->env.vars, FALSE);
	if (!ft_strncmp("echo", command, size))
		ft_echo(node->cmd);
	is_parent_builtin(head, node);
	free_btree(head->root);
	free_head(head);
	exit(0);
}

int	is_parent_builtin(t_head *head, t_btree *node)
{
	char	*command;
	int		ok;
	int		size;

	ok = 1;
	if (node->cmd->args == NULL)
	{
		head->is_parent = 0;
		return (0);
	}
	command = node->cmd->args[0];
	size = ft_strlen(command);
	if (!ft_strncmp("exit", command, size) && head->n_cmds == 1)
		ok = ft_exit(head, node);
	if (!ft_strncmp("cd", command, size))
		ok = ft_cd(head, node);
	if (!ft_strncmp("export", command, size))
		ok = ft_export(head, node, NULL);
	if (!ft_strncmp("unset", command, size))
		ok = ft_unset(node->cmd, &head->env);
	head->is_parent = ok;
	return (ok);
}
