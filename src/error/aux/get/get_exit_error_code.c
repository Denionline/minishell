#include "minishell.h"

int	get_exit_error_code(int error_id)
{
	if (error_id == ERR_CMD || error_id == ERR_NOT_FOUND)
		return (127);
	if (error_id == ERR_PER || error_id == ERR_DIRECTORY)
		return (126);
	if (error_id == ERR_SYNTAX_ERROR || error_id == ERR_QUOTES_ERROR)
		return (2);
	return (1);
}
