
#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_quotes
{
	char	quote;
	int		s;
	int		d;
}	t_quotes;

void	parse(t_head *head, char *prompt);

#endif