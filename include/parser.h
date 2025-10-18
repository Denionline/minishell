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

typedef struct s_arg {
	t_quotes	quotes;
	int			current_size;
	char		*string;
	int			lstring;
	int			pos;
	int			i;
}	t_arg;

void	parse(t_head *head, char *prompt);
t_file	heredoc(char *eof);

// parse/aux/
int		handle_file(t_head *head, t_files *files, char *prompt, int op);

// parse/aux/get/
char	*get_var_path(char *prefix, char **envp);
int		get_operator(char *value);
void	print(t_btree *token);
int		get_operator_size(int operator);
int		is_arrow_operator(int operator);
int		verify_quotes(t_quotes *quotes, char c);
int		is_main_quote_closed(t_quotes *quotes);

// parse/aux/string_argument/
char	*string_argument(char *string, char **envp, int *len);
int		string_argument_size(char *string, char **envp);
// parse/aux/string_argument/aux/
int		is_tohandle_backslash(char *c, char quote);
int		is_var_char(char c);
// aux/btree/
void	btree_add_as_first(t_btree **root, t_btree *new_node);
void	btree_set_file_last_cmd(t_btree **root, t_files **files);

#endif
