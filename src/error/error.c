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
	if (error_id == ERR_CMD)
		return (127);
	if (error_id == ERR_PER)
		return (126);
	if (error_id == 5)
		return (2);
	if (error_id == 6)
		return (2);
	if (error_id == 126)
		return (126);
	if (error_id == 7)
		return (127);
	return (1);
}

static int	is_to_exit(int error_id)
{
	if (error_id == 3)
		return (FALSE);
	if (error_id == 4)
		return (FALSE);
	if (error_id == 5 || error_id == 6)
		return (FALSE);
	if (error_id == 8)
		return (FALSE);
	if (error_id == 15)
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
	if (error->id == 0 || error->id == 1)
	{
		if (error->id == 0 && access(error->msg.argument, F_OK) == -1)
			return ("No such file or directory");
		return ("Permission denied");
	}
	if (error->id == 2)
		return ("command not found");
	if (error->id == 10)
		return ("Permission denied");
	if (error->id == 3)
	{
		if (access(error->msg.argument, F_OK) == -1)
			return ("No such file or directory");
		return ("Not a directory");
	}
	if (error->id == 4)
		return ("too many arguments");
	if (error->id == 5)
		return ("syntax error near unexpected token");
	if (error->id == 6)
		return ("quotes unclosed");
	if (error->id == 126)
		return ("Is a directory");
	if (error->id == 7)
		return ("No such file or directory");
	if (error->id == 8)
	{
		if (!error->msg.argument && is_variable_exist("HOME", head->env.vars) < 0)
			return ("HOME not set");
		if (is_variable_exist("OLDPWD", head->env.vars) < 0)
			return ("OLDPWD not set");
	}
	if (error->id == 15)
		return ("not a valid identifier");
	return (NULL);
}

static void	handle_error_info(t_head *head, t_error *error)
{
	if (error->string)
		error->msg.argument = error->string;
	else
	{
		if (error->id == 3 || error->id == 8)
		{
			error->msg.where = error->node->cmd->args[0];
			error->msg.argument = error->node->cmd->args[1];
		}
		else if (error->id == 1)
			error->msg.argument = error->node->files.out.name;
		else if (error->id == 0)
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

	// 2	= ERR_CMD
	// 10	= ERR_PER
	// 3	= ERR_CD
	// 4	= ERR_TOO_MANY_ARGS
	// 5 6	= ERR_SYNTAX_ERROR
	// 126	= ERR_DIRECTORY
	// 7	= ERR_NOT_FOUND
	// 8	= ERR_HOME_OLDPWD
	// 15	= ERR_EXPORT