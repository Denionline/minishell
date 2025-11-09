#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include "minishell.h"

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
	int			*len;
	int			to_expand;
}	t_arg;

void	parse(t_head *head, char *prompt);
t_file	heredoc(t_head *head, char *eof);
void	new_shlvl(char **env);
int		is_variable_exist(char *variable, char **vars);

// parse/aux/
int		handle_file(t_head *head, t_files *files, char *prompt, int op);

// parse/aux/get/
void	print(t_head *head);
char	*get_var_path(char *prefix, char **envp);
int		get_operator(char *value);
int		get_operator_size(int operator);
int		is_arrow_operator(int operator);
int		verify_quotes(t_quotes *quotes, char c, int is_heredoc);
int		is_quote_closed(t_quotes *quotes);
char	**get_realloc_args(char **old_args, int new_len, char *new_value);

t_cmd	*get_command(t_head *head, char *prompt, t_files *files);
char	*get_valid_path(t_env *env, char *command);

// parse/aux/string_argument/
char	*string_argument(t_head *head, char *string, t_arg arg);
void	string_argument_size(t_arg *arg, char *string, char **envp);
// parse/aux/string_argument/aux/
int		is_tohandle_backslash(char *c, char quote);
int		is_var_char(char c);
// aux/btree/
void	btree_add_as_first(t_btree **root, t_btree *new_node);
void	btree_set_file_last_cmd(t_btree **root, t_files **files);

// functions/env/
int		ft_env(char **env, int by_export);
int		ft_echo(t_cmd *cmd);
int		ft_export(t_head *head, t_btree *node);
int		ft_unset(t_cmd *cmd, t_env *env);

int		is_valid_argument(char *arg, int op, int op_after);

#endif
