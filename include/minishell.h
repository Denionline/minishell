
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
}	t_cmd;

typedef struct s_token
{
	char			*identifier;
	t_cmd			*cmd;
	struct s_token	*left;
	struct s_token	*right;
}	t_token;

typedef struct s_head
{
	t_token	*tokens;
	char	**paths;
	char	**envp;
}	t_head;

void	initializer(t_head **head, int argc, char *argv[], char *envp[]);
int		minishell(t_head *head);
void	parse(t_head *head, char *prompt);

// aux/
int		is_operator(char *value);
void	print(t_head *head);

// aux/btree/
t_token	*btree_create(char *identifier, t_cmd *cmd, t_token *left, t_token *right);
void	btree_add_last_left(t_token **root, t_token *new_token);
void	btree_add_last_right(t_token **root, t_token *new_token);

// aux/get/
int		get_array_len(char **array);
char	*get_valid_path(char **paths, char *command);
char	**get_paths(char *env[]);

// verify/
int		end(t_head *head, int status, char *description);

#endif