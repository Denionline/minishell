/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:41:44 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 19:26:26 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUXILIARY_H
# define AUXILIARY_H

# include "minishell.h"

void	new_shlvl(char **env);
int		is_quotes_valid(char *s);
int		is_variable_exist(char *variable, char **vars);
int		is_directory(char *string);
int		is_var_char(char c, int pos);
int		get_variable_size(char *string);

// get
char	*get_valid_path(t_env *env, char *command);
char	**get_realloc_args(char **old_args, int new_len, char *new_value);
char	*get_var_path(char *prefix, char **envp);
int		get_size_double_array(char **array);

// free_all.c
void	free_error(t_head *head, t_btree *node, int *fd);
void	free_head(t_head *head);

void	free_btree(t_btree *node);
void	free_node(t_btree *node);
void	free_db_str(char **db_str);
void	close_fd(int *fd);

#endif