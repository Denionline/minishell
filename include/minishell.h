#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <limits.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>
# include "libft/include/libft.h"
# include "structs.h"
# include "parser.h"
# include "execute.h"
# include "error.h"
# include <signal.h>

# define RL(x) "\001" x "\002"

# define RESET       RL("\033[0m")
# define BOLD        RL("\033[1m")

# define BLACK       RL("\033[30m")
# define RED         RL("\033[31m")
# define GREEN       RL("\033[32m")
# define YELLOW      RL("\033[33m")
# define BLUE        RL("\033[34m")
# define MAGENTA     RL("\033[35m")
# define CYAN        RL("\033[36m")
# define WHITE       RL("\033[37m")

# define LGRAY       RL("\033[90m")
# define LRED        RL("\033[91m")
# define LGREEN      RL("\033[92m")
# define LYELLOW     RL("\033[93m")
# define LBLUE       RL("\033[94m")
# define LMAGENTA    RL("\033[95m")
# define LCYAN       RL("\033[96m")
# define LWHITE      RL("\033[97m")

enum identifiers
{
	COMMAND,
	PIPE,
	ARROW_LEFT,
	DOUBLE_ARROW_LEFT,
	ARROW_RIGHT,
	DOUBLE_ARROW_RIGHT,
};

void	initializer(t_head **head, int argc, char *argv[], char *envp[]);
int		minishell(t_head *head);
void	prompt_prefix(char buffer[9999]);

// aux/get/
int		get_size_double_array(char **array);

// aux/btree/
t_btree	*btree_create(int identifier, t_cmd *cmd, t_btree *left,
			t_btree *right);
void	btree_add_last_left(t_btree **root, t_btree *new_token);
void	btree_add_last_right(t_btree **root, t_btree *new_token);

// verify/
int		end(t_head *head, int status, char *description);

#endif
