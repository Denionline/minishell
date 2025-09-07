
#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include "libft/include/libft.h"

typedef struct s_cmd
{
	char	**args;
	char	*path;
	char	*right_sig;
}	t_cmd;

typedef struct s_head
{
	t_cmd	*cmds;
	char	**envp;
}	t_head;

void	initializer(t_head **head, int argc, char *argv[], char *envp[]);
int		minishell(t_head *head);
void	parse(t_head *head, char *prompt);
void	print_cmds(t_head *head);

// aux/
int		get_array_len(char **array);
int		is_signal(char *value);

// verify/
int		end(t_head *head, int status, char *description);

#endif