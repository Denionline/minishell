#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct	s_fd
{
	int	in;
	int	out;
}		t_fd;

typedef struct s_file
{
	char	*name;
	int		flags;
	int		exists;
	int		fd;
}	t_file;

typedef struct s_files
{
	t_file	in;
	t_file	out;
}	t_files;

typedef struct s_cmd
{
	char	**args;
	char	*path;
}	t_cmd;

typedef struct s_btree
{
	int				identifier;
	t_cmd			*cmd;
	t_files			files;
	struct s_btree	*left;
	struct s_btree	*right;
	t_fd	fd;
}	t_btree;

typedef struct s_head
{
	t_btree	*root;
	char	**paths;
	char	**envp;
	int		exit_code;
	int		n_cmds;
	t_file	file;
	pid_t	*pid;
	t_fd	fd;
	int	index;
}	t_head;

#endif
