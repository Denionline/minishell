/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:22:48 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/21 18:37:46 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_or_set(char *variable, int lvar, char *value, t_env *env)
{
	char	*temp;
	int		pos;

	pos = is_variable_exist(variable, env->vars);
	if (pos >= 0)
	{
		temp = env->vars[pos];
		if (value[lvar] == '=')
			env->vars[pos] = ft_strdup(value);
		else if (value[lvar] == '+' && value[lvar + 1] == '=')
			env->vars[pos] = ft_strjoin(temp, value + lvar + 2);
	}
	else
	{
		temp = ft_strjoin(variable, value + lvar + (value[lvar] == '+'));
		env->vars = get_realloc_args(env->vars, ++env->n_vars, ft_strdup(temp));
	}
	free(temp);
	free(variable);
}

static int	is_char_valid_to_export(char c)
{
	if (c == '=')
		return (TRUE);
	if (c == '+')
		return (TRUE);
	if (c == '\0')
		return (TRUE);
	return (FALSE);
}

static int	handle_variable(t_head *head, char *complete_var)
{
	int	lvar;

	lvar = 0;
	while (is_var_char(complete_var[lvar], lvar))
		lvar++;
	if (is_char_valid_to_export(complete_var[lvar]) && lvar > 0)
		change_or_set(
			ft_substr(complete_var, 0, lvar),
			lvar,
			complete_var,
			&head->env
			);
	else
		ft_error(head, (t_error){
			.id = ERR_EXPORT,
			.string = complete_var,
			.msg.where = "export"}
			);
	return (0);
}

int	ft_export(t_head *head, t_btree *node, char *variable_to_change)
{
	int	n_args;
	int	i;

	if (variable_to_change)
		return (handle_variable(head, variable_to_change));
	n_args = get_size_double_array(node->cmd->args);
	if (n_args == 1)
		return (ft_env(get_ascii_order(head->env.vars), TRUE));
	i = 0;
	while (++i < n_args)
		handle_variable(head, node->cmd->args[n_args - i]);
	return (0);
}
