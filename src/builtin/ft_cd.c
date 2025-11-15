#include "minishell.h"

void	set_old_and_pwd(t_head *head)
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

int	ft_cd(t_head *head, t_btree *node)
{
	char	*path;

	path = NULL;
	if (node->cmd->args[1])
		path = ft_strdup(node->cmd->args[1]);
	if (node->cmd->args[1] && node->cmd->args[2])
	{
		ft_error(head, node, NULL, 4);
		free(path);
		return (0);
	}
	else if (!path)
		path = get_var_path("HOME", head->env.vars);
	else if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
	{
		free(path);
		path = get_var_path("OLDPWD",  head->env.vars);
	}
	if (path != NULL)
	{
		if (chdir(path) == -1)
			ft_error(head, node, NULL, 3);
		else
		{
			define_exit_code(0, TRUE);
			set_old_and_pwd(head);
		}
	}
	else
		ft_error(head, node, NULL, 8);
	free(path);
	return (0);
}
