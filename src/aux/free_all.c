
#include "minishell.h"

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

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

void	free_node(t_btree *node)
{
	if (node->cmd)
	{
		if (node->cmd->args)
			free_db_str(node->cmd->args);
		if (node->cmd->path)
			free(node->cmd->path);
		free(node->cmd);
	}
	free(node);
}

void	free_btree(t_btree *node)
{
	if (node->left)
	{
		free_btree(node->left);
		if (node->right)
			free_btree(node->right);
	}
	if (node)
		free_node(node);
}
/*
void	free_all(t_head *head, t_btree *btree, int *fd)
{
	(void)*head;
	if (fd)
		close_fd(fd);
	if (btree)
		free_btree(btree);
}*/
