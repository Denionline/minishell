#include "minishell.h"

static void	print_error(t_msg msg)
{
	if (!msg.error_description)
		return ;
	ft_putstr_fd("minishell: ", 2);
	if (msg.where)
	{
		ft_putstr_fd(msg.where, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg.argument)
	{
		ft_putstr_fd(msg.argument, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg.error_description, 2);
	ft_putstr_fd("\n", 2);
}

static int	get_exit_error_code(int error_id)
{
	if (error_id == ERR_CMD || error_id == ERR_NOT_FOUND)
		return (127);
	if (error_id == ERR_PER || error_id == ERR_DIRECTORY)
		return (126);
	if (error_id == ERR_SYNTAX_ERROR || error_id == ERR_QUOTES_ERROR)
		return (2);
	return (1);
}

static int	is_to_exit(int error_id)
{
	if (error_id == ERR_CD)
		return (FALSE);
	if (error_id == ERR_TOO_MANY_ARGS)
		return (FALSE);
	if (error_id == ERR_SYNTAX_ERROR)
		return (FALSE);
	if (error_id == ERR_QUOTES_ERROR)
		return (FALSE);
	if (error_id == ERR_HOME_OLDPWD)
		return (FALSE);
	if (error_id == ERR_EXPORT)
		return (FALSE);
	return (TRUE);
}

static void	end_error(t_head *head, t_error error)
{
	error.exit_code = get_exit_error_code(error.id);
	if (is_to_exit(error.id))
	{
		free_error(head, error.node, error.fds);
		exit(define_exit_code(error.exit_code, TRUE));
	}
	define_exit_code(error.exit_code, TRUE);
}

static char	*get_error_description(t_head *head, t_error *error)
{
	if (error->id == ERR_REDIR_IN || error->id == ERR_REDIR_OUT)
	{
		if (error->id == 0 && access(error->msg.argument, F_OK) == -1)
			return ("No such file or directory");
		return ("Permission denied");
	}
	if (error->id == ERR_CMD)
		return ("command not found");
	if (error->id == ERR_PER)
		return ("Permission denied");
	if (error->id == ERR_CD)
	{
		if (access(error->msg.argument, F_OK) == -1)
			return ("No such file or directory");
		return ("Not a directory");
	}
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
	if (error->id == ERR_HOME_OLDPWD)
	{
		if (!error->msg.argument && is_variable_exist("HOME", head->env.vars) < 0)
			return ("HOME not set");
		if (is_variable_exist("OLDPWD", head->env.vars) < 0)
			return ("OLDPWD not set");
	}
	if (error->id == ERR_EXPORT)
		return ("not a valid identifier");
	return (NULL);
}

static void	handle_error_info(t_head *head, t_error *error)
{
	if (error->string)
		error->msg.argument = error->string;
	else if (error->node)
	{
		if (error->id == ERR_CD || error->id == ERR_HOME_OLDPWD)
		{
			error->msg.where = error->node->cmd->args[0];
			error->msg.argument = error->node->cmd->args[1];
		}
		else if (error->id == ERR_REDIR_OUT)
			error->msg.argument = error->node->files.out.name;
		else if (error->id == ERR_REDIR_IN)
			error->msg.argument = error->node->files.in.name;
		else
			error->msg.argument = error->node->cmd->args[0];
	}
	error->msg.error_description = get_error_description(head, error);
}

void	ft_error(t_head *head, t_error error)
{
	handle_error_info(head, &error);
	print_error(error.msg);
	end_error(head, error);
}
