#include "minishell.h"

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
