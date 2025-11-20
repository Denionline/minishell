/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:22:57 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:22:58 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	if (is_strmatch(command, "exit"))
		return (TRUE);
	if (is_strmatch(command, "pwd"))
		return (TRUE);
	if (is_strmatch(command, "cd"))
		return (TRUE);
	if (is_strmatch(command, "env"))
		return (TRUE);
	if (is_strmatch(command, "export"))
		return (TRUE);
	if (is_strmatch(command, "unset"))
		return (TRUE);
	if (is_strmatch(command, "echo"))
		return (TRUE);
	return (FALSE);
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
	if (!node->cmd->args)
	{
		if (!node->files.in.exists && !node->files.out.exists)
		{
			head->is_parent = 0;
			return (define_exit_code(0, TRUE));
		}
		return (ok);
	}
	command = node->cmd->args[0];
	if (is_strmatch(command, "exit") && head->n_cmds == 1)
		ok = ft_exit(head, node);
	if (is_strmatch(command, "cd"))
		ok = ft_cd(head, node);
	if (is_strmatch(command, "export"))
		ok = ft_export(head, node, NULL);
	if (is_strmatch(command, "unset"))
		ok = ft_unset(node->cmd, &head->env);
	head->is_parent = ok;
	return (ok);
}
