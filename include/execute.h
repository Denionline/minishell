
#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

//execute
int	hierarchy_btree(t_head *head, t_btree *node);
void	execute_with_pipe(t_head *head, t_btree *node);
int	execute(t_head *head, t_btree *node);
pid_t	child_process(t_head *head, t_btree *node);

void	free_all(t_head *head, t_btree *node, int *fd);
void	free_btree(t_btree *node);
void	free_node(t_btree *node);
void	free_db_str(char **db_str);
void	close_fd(int *fd);


#endif
