#include "minishell.h"

int	ft_pwd(t_btree *node)
{
	char	buffer[100];

	(void)*node;
	ft_putstr_fd(getcwd(buffer, 100), 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
