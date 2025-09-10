
#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/include/libft.h"

typedef struct s_cmd
{
	char	**args;
	char	*path;
	char	*right_sig;
	int	status;
}	t_cmd;

typedef struct s_head
{
	t_cmd	*cmds;
	char	**envp;
}	t_head;

void	initializer(t_head **head, int argc, char *argv[], char *envp[]);
void	parse(t_head *head, char *prompt);
int		minishell(t_head *head);

// aux/
int		get_array_len(char **array);
int		is_signal(char *value);

// verify/
int		end(t_head *head, int status, char *description);

//execute/
void	hierarchy(t_head *head);
void	execute(t_head *head, t_cmd cmd);

#endif
