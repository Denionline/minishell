/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:09:17 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 15:44:46 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

/* ************************************************************************** */
/*                                  ENUMS                                     */
/* ************************************************************************** */

enum e_node_identifier
{
	COMMAND = 1,
	PIPE,
	ANDPERCENT,
	ARROW_LEFT,
	DOUBLE_ARROW_LEFT,
	ARROW_RIGHT,
	DOUBLE_ARROW_RIGHT,
};

enum e_erro_identifier
{
	ERR_REDIR_IN = 1,
	ERR_REDIR_OUT,
	ERR_CMD,
	ERR_PER,
	ERR_CD,
	ERR_EXPORT,
	ERR_MAX_ARGS,
	ERR_SYNTAX_ERROR,
	ERR_QUOTES_ERROR,
	ERR_DIR,
	ERR_NOT_FOUND,
	ERR_HOME_OLDPWD,
	ERR_MALLOC,
};

/* ************************************************************************** */
/*                                  PARSING                                   */
/* ************************************************************************** */

typedef struct s_quotes
{
	char	quote;
	int		s;
	int		d;
}	t_quotes;

typedef struct s_arg
{
	t_quotes	quotes;
	int			current_size;
	char		*string;
	int			lstring;
	int			pos;
	int			i;
	int			new_len;
	int			was_expanded;
	int			*len;
	int			to_expand;
}	t_arg;

/* ************************************************************************** */
/*                                 EXECUTION                                  */
/* ************************************************************************** */

typedef struct s_pipe
{
	int	pipe_fd[2];
	int	flag;
}		t_pipe;

/* ************************************************************************** */
/*                                  GENERAL                                   */
/* ************************************************************************** */

typedef struct s_file
{
	char	*name;
	int		flags;
	int		exists;
	int		fd;
	int		access;
	int		operator;
	int		is_there_heredoc;
}	t_file;

typedef struct s_files
{
	t_file	in;
	t_file	out;
}	t_files;

typedef struct s_cmd
{
	char	**args;
	char	*path;
	int		args_len;
}	t_cmd;

typedef struct s_btree
{
	int				identifier;
	t_cmd			*cmd;
	t_files			files;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

typedef struct s_env
{
	char	**vars;
	int		n_vars;
}	t_env;

typedef struct s_head
{
	t_btree	*root;
	t_env	env;
	int		n_cmds;
	int		cmd_size;
	t_files	files;
	pid_t	*pid;
	int		index;
	int		is_parent;
	t_pipe	pipe;
	int		to_stop;
}	t_head;

/* ************************************************************************** */
/*                                   ERRORS                                   */
/* ************************************************************************** */

typedef struct s_msg
{
	char	*where;
	char	*argument;
	char	*error_description;
}	t_msg;

typedef struct s_error
{
	int		id;
	int		exit_code;
	char	*string;
	t_btree	*node;
	int		*fds;
	t_msg	msg;
}	t_error;

#endif