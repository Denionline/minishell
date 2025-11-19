#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

// 0	= ERR_REDIR_IN
// 1	= ERR_REDIR_OUT
// 2	= ERR_CMD
// 10	= ERR_PER
// 3	= ERR_CD
// 4	= ERR_TOO_MANY_ARGS
// 5	= ERR_SYNTAX_ERROR
// 6	= ERR_QUOTES_ERROR
// 126	= ERR_DIRECTORY
// 7	= ERR_NOT_FOUND
// 8	= ERR_HOME_OLDPWD
// 15	= ERR_EXPORT

enum erro_identifier
{
	ERR_REDIR_IN = 1,
	ERR_REDIR_OUT,
	ERR_CMD,
	ERR_PER,
	ERR_CD,
	ERR_EXPORT,
	ERR_TOO_MANY_ARGS,
	ERR_SYNTAX_ERROR,
	ERR_QUOTES_ERROR,
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

int		is_to_exit(int error_id);
void	print_error(t_msg msg);
int		get_exit_error_code(int error_id);
char	*get_error_description(t_head *head, t_error *error);

#endif