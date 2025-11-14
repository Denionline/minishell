#include "minishell.h"

int	ft_pwd(void)
{
	char	buffer[999];

	if (getcwd(buffer, 999) != NULL)
		ft_putendl_fd(buffer, 1);
	else
		return (define_exit_code(1, TRUE));
	return (define_exit_code(0, TRUE));
}
