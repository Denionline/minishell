
#include "minishell.h"

int	is_operator(char *value)
{
	if (!value || !*value)
		return (0);
	if (value[0] == '|' && value[1] == '|')
		return (OR);
	if (value[0] != '|' && value[1] == '|' && value[2] != '|')
		return (PIPE);
	if (value[0] == '&' && value[1] == '&')
		return (AND);
	if (value[0] == '<' && value[1] == '<')
		return (DOUBLE_ARROW_LEFT);
	if (value[0] == '>' && value[1] == '>')
		return (DOUBLE_ARROW_RIGHT);
	if (value[0] != '<' && value[1] == '<' && value[2] != '<')
		return (ARROW_LEFT);
	if (value[0] != '>' && value[1] == '>' && value[2] != '>')
		return (ARROW_RIGHT);
	return (0);
}
