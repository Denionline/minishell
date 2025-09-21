#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_fd
{
	int	in;
	int	out;
}	t_fd;

typedef struct s_cmd
{
	char	**args;
	char	*path;
}	t_cmd;

typedef struct s_btree
{
	int				identifier;
	t_cmd			*cmd;
	t_fd			fd;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

typedef struct s_head
{
	t_btree	*root;
	char	**paths;
	char	**envp;
	int		exit_code;
	t_fd	fd;
	int	n_cmds;
	pid_t	*pid;
	int	index;
}	t_head;

#endif
