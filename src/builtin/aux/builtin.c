#include "minishell.h"

int	get_builtin(char *command)
{
	if (is_strmatch(command, "exit"))
		return (PARENT_BUILTIN);
	if (is_strmatch(command, "cd"))
		return (PARENT_BUILTIN);
	if (is_strmatch(command, "export"))
		return (PARENT_BUILTIN);
	if (is_strmatch(command, "unset"))
		return (PARENT_BUILTIN);
	if (is_strmatch(command, "echo"))
		return (CHILD_BUILTIN);
	if (is_strmatch(command, "pwd"))
		return (CHILD_BUILTIN);
	if (is_strmatch(command, "env"))
		return (CHILD_BUILTIN);
	return (0);
}

void	call_builtin(t_head *head, t_btree *node)
{
	char	*command;

	command = node->cmd->args[0];
	if (is_strmatch(command, "pwd"))
		ft_pwd();
	if (is_strmatch(command, "env"))
		ft_env(head->env.vars, FALSE);
	if (is_strmatch(command, "echo"))
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
	if (is_strmatch(command, "exit") && head->n_cmds == 1)
		ft_exit(head, node);
	if (is_strmatch(command, "cd"))
		ft_cd(head, node);
	if (is_strmatch(command, "export"))
		ft_export(head, node, NULL);
	if (is_strmatch(command, "unset"))
		ft_unset(node->cmd, &head->env);
	head->is_parent = ok;
	return (ok);
}
