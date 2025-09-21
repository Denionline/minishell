
#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

//execute
int	hierarchy_btree(t_head *head, t_btree *node);
void	execute_with_pipe(t_head *head, t_btree *node);
int	execute(t_head *head, t_btree *node);
pid_t	child_process(t_head *head, t_btree *node);
int     count_cmds(t_btree *node, int j);
void    execute_manager(t_head *head);
int     wait_list(t_head *head);
void    fd_organizer(t_head *head, t_btree *node, int *fd);

void	free_all(t_head *head, t_btree *node, int *fd);
void	free_btree(t_btree *node);
void	free_node(t_btree *node);
void	free_db_str(char **db_str);
void	close_fd(int *fd);
void    reset_all(t_head *head, char *prompt);


#endif
