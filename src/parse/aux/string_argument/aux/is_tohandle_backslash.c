
#include "minishell.h"

int	is_tohandle_backslash(char *c, char quote)
{
	if (*c != '\\' || quote == '\'')
		return (0);
	c++;
	if (*c == '\"')
		return (1);
	if (*c == '\'')
		return (1);
	if (*c == '$')
		return (1);
	if (*c == '\\')
		return (1);
	if (*c == 'n')
		return (1);
	return (0);
}
