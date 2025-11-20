#include "minishell.h"

static char	*verify_variables_to_get(t_head *head, t_error *error)
{
	if (error->id == ERR_REDIR_IN && access(error->msg.argument, F_OK) == -1)
		return ("No such file or directory");
	if (error->id == ERR_REDIR_IN || error->id == ERR_REDIR_OUT)
		return ("Permission denied");
	if (error->id == ERR_CD)
	{
		if (access(error->msg.argument, F_OK) == -1)
			return ("No such file or directory");
		return ("Not a directory");
	}
	if (error->id == ERR_HOME_OLDPWD)
	{
		if (!error->msg.argument && is_variable_exist(
			"HOME", head->env.vars
		) < 0)
			return ("HOME not set");
		if (is_variable_exist("OLDPWD", head->env.vars) < 0)
			return ("OLDPWD not set");
	}
	return (NULL);
}

char	*get_error_description(t_head *head, t_error *error)
{
	if (error->id == ERR_CMD)
		return ("command not found");
	if (error->id == ERR_PER)
		return ("Permission denied");
	if (error->id == ERR_TOO_MANY_ARGS)
		return ("too many arguments");
	if (error->id == ERR_SYNTAX_ERROR)
		return ("syntax error near unexpected token");
	if (error->id == ERR_QUOTES_ERROR)
		return ("quotes unclosed");
	if (error->id == ERR_DIRECTORY)
		return ("Is a directory");
	if (error->id == ERR_NOT_FOUND)
		return ("No such file or directory");
	if (error->id == ERR_EXPORT)
		return ("not a valid identifier");
	return (verify_variables_to_get(head, error));
}
