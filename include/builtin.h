/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:44:51 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 12:35:52 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

// /aux
int		is_builtin(char *command);
int		is_parent_builtin(t_head *head, t_btree *btree);
void	call_builtin(t_head *head, t_btree *node);
int		is_str_alpha(char *string);

// /aux/get
char	**get_ascii_order(char **vars);

int		ft_pwd(void);
int		ft_cd(t_head *head, t_btree *node);
int		ft_exit(t_head *head, t_btree *node);
int		ft_env(char **env, int by_export);
int		ft_echo(t_cmd *cmd);
int		ft_export(t_head *head, t_btree *node, char *string);
int		ft_unset(t_cmd *cmd, t_env *env);

#endif
