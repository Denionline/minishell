
#include "minishell.h"

void	init_infile(char *name, t_head *head)
{
	head->root->fd.in = -1;
	head->root->fd.out = -1;
	head->root->fd.in = open(name, O_RDONLY);
//	printf("%d", head->root->fd.in);
}
