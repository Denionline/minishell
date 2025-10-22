
#include "minishell.h"

// static char	**realloc_args(char **old_args, int new_len)
// {
// 	char	**new_args;
// 	int		i;

// 	new_args = ft_calloc(new_len + 1, sizeof(char *));
// 	if (!new_args)
// 		return (NULL);
// 	if (old_args)
// 	{
// 		i = 0;
// 		while (old_args[i])
// 		{
// 			new_args[i] = old_args[i];
// 			i++;
// 		}
// 		new_args[i] = NULL;
// 		free(old_args);
// 	}
// 	return (new_args);
// }

void	ft_export(t_btree *node, char **envp)
{
	int	i;

	(void)envp;
	i = 0;
	ft_putendl_fd(node->cmd->args[i], 1);
	while (node->cmd->args[i])
	{
		i++;
	}
}