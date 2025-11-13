#include "minishell.h"

int	ft_cd(t_head *head, t_btree *node)
{
	char	*home;
	char	*pwd;
	char	*oldpwd;
	char	buffer[100];

	if (node->cmd->args[2])
		ft_error(head, node, NULL, 4);
	else if (node->cmd->args[1] == NULL)
	{
		home = getenv("HOME");
		printf("%s\n", home);
		chdir(home);
	}
	else if (chdir(node->cmd->args[1]) == -1)
		ft_error(head, node, NULL, 3);
	else
	{
		oldpwd = getenv("PWD");
		//printf("%s\n", oldpwd);
		pwd = getcwd(buffer, 100);
		//printf("%s\n", pwd);
	}
	return (0);
}
