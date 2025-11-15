#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_pipe
{
	int	pipe_fd[2];
	int	flag;
}		t_pipe;

typedef struct s_file
{
	char	*name;
	int		flags;
	int		exists;
	int		fd;
	int		access;
	int		operator;
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
	int		args_len;
}	t_cmd;

typedef struct s_btree
{
	int				identifier;
	t_cmd			*cmd;
	t_files			files;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

typedef struct s_env
{
	char	**vars;
	int		n_vars;
}	t_env;

typedef struct s_head
{
	t_btree	*root;
	t_env	env;
	int		n_cmds;
	int		cmd_size;
	t_files	files;
	pid_t	*pid;
	int		index;
	int		is_parent;
	t_pipe	pipe;
	int		to_stop;
}	t_head;

#endif
