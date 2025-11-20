/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:22:55 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 19:15:16 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_old_and_pwd(t_head *head)
{
	char	*pwd;
	char	buffer[999];
	char	*oldpwd;
	char	*current;

	current = get_var_path("PWD", head->env.vars);
	if (current)
	{
		oldpwd = ft_strjoin("OLDPWD=", current);
		free(current);
		ft_export(head, NULL, oldpwd);
		free(oldpwd);
	}
	pwd = getcwd(buffer, 999);
	if (pwd)
	{
		pwd = ft_strjoin("PWD=", pwd);
		ft_export(head, NULL, pwd);
		free(pwd);
	}
}

static char	*cd_get_path(t_head *head, char *path)
{
	if (!path)
		path = get_var_path("HOME", head->env.vars);
	else if (is_strmatch(path, "-"))
	{
		free(path);
		path = get_var_path("OLDPWD", head->env.vars);
		ft_putendl_fd(path, 1);
	}
	return (path);
}

int	ft_cd(t_head *head, t_btree *node)
{
	char	*path;

	path = NULL;
	if (node->cmd->args[1])
		path = ft_strdup(node->cmd->args[1]);
	if (node->cmd->args[1] && node->cmd->args[2])
	{
		ft_error(head, (t_error){.id = ERR_MAX_ARGS, .node = node});
		return (free(path), 0);
	}
	path = cd_get_path(head, path);
	if (path != NULL)
	{
		if (chdir(path) == -1)
			ft_error(head, (t_error){.id = ERR_CD, .node = node});
		else
		{
			define_exit_code(0, TRUE);
			set_old_and_pwd(head);
		}
	}
	else
		ft_error(head, (t_error){.id = ERR_HOME_OLDPWD, .node = node});
	free(path);
	return (0);
}
