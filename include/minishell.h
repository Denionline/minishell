
#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdlib.h>
# include "libft/include/libft.h"

typedef struct s_cmd
{
	char	**args;
	char	*path;
}	t_cmd;

typedef struct s_head
{
	t_cmd	*cmds;
	char	**envp;
}	t_head;

void	initializer(t_head **head, int argc, char *argv[], char *envp[]);
void	parse(t_head *head, char *prompt);
int		minishell(t_head *head);

#endif