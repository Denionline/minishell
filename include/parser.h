
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

// parse/aux/get/
char	*get_string_argument(char *string);
int		get_next_increase(int operator, char *prompt);

int		operator_size(int operator);
// aux/btree/
void	btree_add_as_first(t_btree **root, t_btree *new_node);

#endif