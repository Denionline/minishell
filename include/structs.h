#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct  s_pipe
{
        int     pipe_fd[2];
        int     flag;
}               t_pipe;

typedef struct s_file
{
	char	*name;
	int		flags;
	int		exists;
	int		fd;
}	t_file;

typedef struct s_files
{
	t_file	*in;
	t_file	*out;
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
	int		exit_code;
	int		n_cmds;
	t_files	files;
	pid_t	*pid;
	int		index;
	t_pipe	pipe;
}	t_head;

#endif
