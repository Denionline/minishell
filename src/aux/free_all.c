
#include "minishell.h"

//function to close fds
void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

//function to free double pointer char
void	free_db_str(char **db_str)
{
	int	i;

	i = 0;
	while (db_str[i])
	{
		free(db_str[i]);
		i++;
	}
	free(db_str);
}

//function to free command struct
void	free_node(t_btree *node)
{
	if (node->cmd)
	{
		free_db_str(node->cmd->args);
		free(node->cmd->path);
		free(node->cmd);
//		node->cmd = NULL;
	}
	free(node);
//	node = NULL;
}

//function to free the binary tree
void	free_btree(t_btree *node)
{
	if (node->left)
	{
		free_btree(node->left);
		if (node->right)
			free_btree(node->right);
	}
	free_node(node);
//	node = NULL;
}

void	free_all(t_head *head, t_btree *btree, int *fd)
{
	(void)*head;
	if (fd)
		close_fd(fd);
	if (btree)
		free_btree(btree);
}
