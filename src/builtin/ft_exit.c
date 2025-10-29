
#include "minishell.h"

void	ft_exit(t_head *head)
{
//	(void)*head;
	free_db_str(head->env.vars);
	head = NULL;
	ft_putendl_fd("exit", 1);
}
