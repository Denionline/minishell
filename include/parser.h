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

void	parse(t_head *head, char *prompt);

// parse/aux/
int	handle_file(t_head *head, t_files *files, char *prompt, int op);

// parse/aux/get/
char	*get_var_path(char *prefix, char **envp);
int		get_operator(char *value);
void	print(t_btree *token);
char	*get_string_argument(char *string, char **envp);
int		get_operator_size(int operator);
int		is_arrow_operator(int operator);
// aux/btree/
void	btree_add_as_first(t_btree **root, t_btree *new_node);
void	btree_set_file_last_cmd(t_btree **root, t_files **files);

#endif
