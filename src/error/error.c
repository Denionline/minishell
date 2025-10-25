
#include "minishell.h"

void	ft_error_infile(t_head *head, t_btree *node)
{
	if (access(node->files.in.name, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(node->files.in.name, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		free_btree(head->root);
		exit(1);
	}
	else if (access(node->files.in.name, R_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(node->files.in.name, 1);
		ft_putstr_fd(": Permission denied\n", 1);
		free_btree(head->root);
		exit(1);	
	}
}

void	ft_error(t_head *head, t_btree *node, int error_type)
{
	if (error_type == 0)
		ft_error_infile(head, node);
}

