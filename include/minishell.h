#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>
# include "libft/include/libft.h"
# include "structs.h"
# include "parser.h"
# include "execute.h"

# define EMPTY				99
# define COMMAND			42
# define AND				11
# define OR					10
# define PIPE				101
# define ARROW_LEFT			33
# define DOUBLE_ARROW_LEFT	333
# define ARROW_RIGHT		44
# define DOUBLE_ARROW_RIGHT	444

void	initializer(t_head **head, int argc, char *argv[], char *envp[]);
int		minishell(t_head *head);

// aux/get/
int		get_size_double_array(char **array);

// aux/btree/
t_btree	*btree_create(int identifier, t_cmd *cmd, t_btree *left,
			t_btree *right);
void	btree_add_last_left(t_btree **root, t_btree *new_token);
void	btree_add_last_right(t_btree **root, t_btree *new_token);

// verify/
int		end(t_head *head, int status, char *description);

//execute/

//signal/
void	signal_handler(void);

#endif
