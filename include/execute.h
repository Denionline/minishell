
#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

void	hierarchy_btree(t_head *head, t_btree *node);
void	execute_with_pipe(t_head *head, t_btree *node);
int	execute(t_head *head, t_btree *node);
pid_t	hild_process(t_head *head, t_btree *node);

#endif
