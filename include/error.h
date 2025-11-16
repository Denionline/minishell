#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

void	ft_error_file(t_head *head, t_btree *node, int *fd, int error);
void	ft_error_command(t_head *head, t_btree *node, int *fd);
void	ft_error_export(t_head *head, char *arg);
void	ft_syntax_error(t_head *head, int error);
void	ft_error_args(t_btree *node);
void	ft_error(t_head *head, t_btree *node, int *fd, int error);

#endif