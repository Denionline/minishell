
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
	while (db_str[i] != NULL)
		i++;
	ft_free_mem(db_str, i); //essa funcao saiu do meu ft_split, o do Ximenes tem tambem?
}

//function to free command struct
void	free_node(btree *node)
{
	if (node->cmds)
	{
		free_db_str(cmds->args);
		free(path);
		free(cmds);
	}
	free(node);
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
	free(node);
}

void	free_all(t_head *head, t_btree *node, pid_t pid, int *fd)
{
	if (fd)
		close_fd(fd);
	if (pid) //eh relevante escrever isso aqui?
		free(pid);
	if (node)
		free_node(node);
	free(head);
}
