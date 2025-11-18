#include "minishell.h"

int	is_to_exit(int error_id)
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
