#include "minishell.h"

void	set_old_and_pwd(t_head *head)
{
	char	*pwd;
	char	*oldpwd;
	char	buffer[999];
	
	oldpwd = getenv("PWD");
	if (getenv("OLDPWD") != NULL)
	{
		oldpwd = ft_strjoin("OLDPWD=", oldpwd);
		ft_export(head, NULL, oldpwd);
	}
	//precisamos export esse novo oldpwd e pwd
	if (getenv("PWD") != NULL)
	{
		pwd = getcwd(buffer, 999);
		pwd = ft_strjoin("PWD=", pwd);
		ft_export(head, NULL, pwd);
	}
}

int	ft_cd(t_head *head, t_btree *node)
{
	char	*path;

	path = node->cmd->args[1];
	if (node->cmd->args[2])
	{
		ft_error(head, node, NULL, 4);
		return (0);
	}
	else if (path == NULL)
		path = getenv("HOME");
	else if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
		path = getenv("OLDPWD");
	if (chdir(path) == -1)
		ft_error(head, node, NULL, 3);
	set_old_and_pwd(head);
	return (0);
}
