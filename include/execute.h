
#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include <fcntl.h>

//execute
int		hierarchy_btree(t_head *head, t_btree *node);
void	execute_with_pipe(t_head *head, t_btree *node);
int		execute(t_head *head, t_btree *node);
pid_t	child_process(t_head *head, t_btree *node);
void	execute_manager(t_head *head);
void	fd_organizer(t_head *head, t_btree *node, int *fd);
int		count_cmds(t_btree *node, int j);

//free
void	free_all(t_head *head, t_btree *node, int *fd);
void	free_btree(t_btree *node);
void	free_node(t_btree *node);
void	free_db_str(char **db_str);
void	close_fd(int *fd);

//built-ins
int		is_builtin(t_btree *node);
void	call_builtin(t_head *head, t_btree *node);
void	ft_pwd(t_btree *node);
void	ft_cd(char *path);

//signals
void	signal_handler(void);
void	signal_tty(void);
void	signal_child(void);

#endif
