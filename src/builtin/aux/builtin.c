#include "minishell.h"

int	is_builtin(char *command)
{
	if (!ft_strncmp("exit", command, 5))
		return (TRUE);
	if (!ft_strncmp("pwd", command, 4))
		return (TRUE);
	if (!ft_strncmp("cd", command, 3))
		return (TRUE);
	if (!ft_strncmp("env", command, 4))
		return (TRUE);
	if (!ft_strncmp("export", command, 7))
		return (TRUE);
	if (!ft_strncmp("unset", command, 6))
		return (TRUE);
	if (!ft_strncmp("echo", command, 5))
		return (TRUE);
	return (FALSE);
}

void	call_builtin(t_head *head, t_btree *node)
{
	const char	*command = node->cmd->args[0];

	if (!ft_strncmp("pwd", command, 4))
		ft_pwd();
	if (!ft_strncmp("env", command, 4))
		ft_env(head->env.vars, FALSE);
	if (!ft_strncmp("echo", command, 5))
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

	ok = 1;
	if (node->cmd->args == NULL)
	{
		head->is_parent = 0;
		return (define_exit_code(0, TRUE));
	}
	command = node->cmd->args[0];
	if (!ft_strncmp("exit", command, 5) && head->n_cmds == 1)
		ok = ft_exit(head, node);
	if (!ft_strncmp("cd", command, 3))
		ok = ft_cd(head, node);
	if (!ft_strncmp("export", command, 7))
		ok = ft_export(head, node, NULL);
	if (!ft_strncmp("unset", command, 6))
		ok = ft_unset(node->cmd, &head->env);
	head->is_parent = ok;
	return (ok);
}
