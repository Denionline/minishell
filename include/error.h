#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

enum erro_identifier
{
	ERR_REDIR_IN,
	ERR_REDIR_OUT,
	ERR_CMD,
	ERR_PER,
	ERR_CD,
	ERR_EXPORT,
	ERR_TOO_MANY_ARGS,
	ERR_SYNTAX_ERROR,
	ERR_DIRECTORY,
	ERR_NOT_FOUND,
	ERR_HOME_OLDPWD,
};

typedef struct s_msg {
	char	*where;
	char	*argument;
	char	*error_description;
}	t_msg;

typedef struct s_error
{
	int		id;
	int		exit_code;
	char	*string;
	t_btree	*node;
	int		*fds;
	t_msg	msg;
}	t_error;

void	ft_error(t_head *head, t_error error);

#endif