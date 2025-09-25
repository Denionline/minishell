
#include "minishell.h"

int	count_cmds(t_btree *node, int j)
{
	static int i;

	if (!node)
		return (0);
	i = j;
	if (node->identifier == COMMAND)
		i += 1;
	else if (node->identifier != COMMAND)
	{
		if (node->left)
			count_cmds(node->left, i);
		if (node->right)
			count_cmds(node->right, i);
	}
	return (i);
}

void	fd_organizer(t_head *head, t_btree *node, int *fd)
{
	(void)fd;
	node->fd.in = -1;
	node->fd.out = -1;
	if (head->n_cmds == 1 && node->fd.in == -1)
		node->fd.in = STDIN_FILENO;
		//nao precisa de dup2, pq so uso esssa variavel para evitar pipe_fd
	else if (node->fd.in != -1)
		dup2(node->fd.in, STDIN_FILENO);
		//aqui precisa do dup2 para redirecionar o fd certo como STDIN
/*	else if (head->index == 0)
	{
		node->fd.in = STDIN_FILENO;

	}*/
	if (head->index == (head->n_cmds - 1))
		node->fd.out = STDOUT_FILENO;
	else if (node->fd.out != -1)
		dup2(node->fd.out, STDOUT_FILENO);
	//modelo novo:
	//	node->files->out.fd != -1
	//ou	node->files->in.fd != -1
}
