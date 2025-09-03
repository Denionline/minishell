
#include "minishell.h"

int	is_signal(char *value)
{
	if (!value)
		return (FALSE);
	if (!ft_strncmp("&&", value, 3))
		return (TRUE);
	if (!ft_strncmp("||", value, 3))
		return (TRUE);
	if (!ft_strncmp("|", value, 2))
		return (TRUE);
	if (!ft_strncmp("<<", value, 3))
		return (TRUE);
	if (!ft_strncmp(">>", value, 3))
		return (TRUE);
	if (!ft_strncmp("<", value, 2))
		return (TRUE);
	if (!ft_strncmp(">", value, 2))
		return (TRUE);
	return (FALSE);
}
