
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
}	t_cmd;

typedef struct s_btree
{
	char			*identifier;
	t_cmd			*cmd;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

typedef struct s_head
{
	t_btree	*root;
	char	**paths;
	char	**envp;
}	t_head;

void	initializer(t_head **head, int argc, char *argv[], char *envp[]);
int		minishell(t_head *head);
void	parse(t_head *head, char *prompt);

// aux/
int		is_operator(char *value);
void	print(t_btree *token);

// aux/btree/
t_btree	*btree_create(char *identifier, t_cmd *cmd, t_btree *left, t_btree *right);
void	btree_add_last_left(t_btree **root, t_btree *new_token);
void	btree_add_last_right(t_btree **root, t_btree *new_token);

// aux/get/
char	**get_cmd_args(char *prompt);
char	*get_valid_path(char **paths, char *command);
char	**get_paths(char *env[]);

// verify/
int		end(t_head *head, int status, char *description);

//execute/

//signal/
void	signal_handler(void);

#endif
