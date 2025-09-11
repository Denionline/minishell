
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
int		minishell(t_head *head);
void	parse(t_head *head, char *prompt);
void	print_cmds(t_head *head);

// aux/
int		is_signal(char *value);

// aux/get/
int		get_array_len(char **array);
char	*get_valid_path(char **paths, char *command);
char	**get_paths(char *env[]);
t_cmd	get_cmd(t_head *head, char *command, char **paths);

// verify/
int		end(t_head *head, int status, char *description);

//execute/

//signal/
void	signal_handler(void);

#endif
