
#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include <fcntl.h>

//process manager
void	execute_manager(t_head *head);
int		hierarchy_btree(t_head *head, t_btree *node);
int		wait_process(t_head *head);

//execute
void	redirect(t_head *head, t_btree *node, int *fd);
void	parent_process(t_head *head, t_btree *node, int *fd);
void	child_process(t_head *head, t_btree *node, int *fd);
void	process(t_head *head, t_btree *node);
void	ft_execute(t_head *head, t_btree *node);

//execute utils
int		count_cmds(t_btree *node, int j);
void	reset_pipe(t_head *head);
void	close_all_fds(t_head *head, t_btree *node, int process);

//free
void	free_all(t_head *head, t_btree *node, int *fd);
void	free_btree(t_btree *node);
void	free_node(t_btree *node);
void	free_db_str(char **db_str);
void	close_fd(int *fd);

//built-ins
int		is_builtin(char *command);
int		is_parent_builtin(t_head *head, t_btree *btree);
void	call_builtin(t_head *head, t_btree *node);
int		ft_pwd(t_btree *node);
int		ft_cd(char *path);
int		ft_exit(t_head *head);

//signals
void	signal_handler(void);
void	signal_tty(void);
void	signal_child(void);

//error
void	ft_error(t_head *head, t_btree *node, int *fd, int error_type);
void	ft_error_file(t_head *head, t_btree *node, int *fd, int error_type);

#endif
