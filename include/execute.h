/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:56:43 by clumertz          #+#    #+#             */
/*   Updated: 2025/11/20 12:24:56 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

// process_manager.c
void	execute_manager(t_head *head);
int		hierarchy_btree(t_head *head, t_btree *node);
int		wait_process(t_head *head);

// execute.c
void	redirect(t_head *head, t_btree *node, int *fd);
void	parent_process(t_head *head, t_btree *node, int *fd);
void	child_process(t_head *head, t_btree *node, int *fd);
void	process(t_head *head, t_btree *node);
void	ft_execute(t_head *head, t_btree *node);

// execute_utils.c
int		count_cmds(t_btree *node, int j);
void	reset_head(t_head *head);
void	close_all_fds(t_head *head, t_btree *node, int process);
void	close_all(t_head *head, t_btree *node, int *fd);
int		define_exit_code(int exit_status, int change);

// /aux/
int		count_cmds(t_btree *node, int j);

#endif
