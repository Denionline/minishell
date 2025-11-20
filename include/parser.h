/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:34:23 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:20:39 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

void	parse(t_head *head, char *prompt);

// parse/aux/
t_file	heredoc(t_head *head, char *eof);
int		is_valid_argument(t_head *head, char *arg, int op, int op_after);
int		handle_file(t_head *head, t_files *files, char *prompt, int op);

// parse/aux/get/
t_cmd	*get_command(t_head *head, char *prompt, t_files *files);
int		get_operator(char *value);
int		get_operator_size(int operator);
int		is_arrow_operator(int operator);

// parse/aux/string_argument/
char	*string_argument(t_head *head, char *string, t_arg arg);
void	string_argument_size(t_arg *arg, char *string, char **envp);

// parse/aux/string_argument/aux/
int		is_quote_closed(t_quotes *quotes);
int		verify_quotes(t_quotes *quotes, char c, int is_heredoc);
int		is_tohandle_backslash(char *c, char quote);

#endif
