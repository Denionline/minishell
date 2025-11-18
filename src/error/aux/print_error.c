#include "minishell.h"

void	print_error(t_msg msg)
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
