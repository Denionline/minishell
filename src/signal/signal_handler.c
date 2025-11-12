#include "minishell.h"

void	signal_handler(t_head *head)
{
	(void)*head;
	if (SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
	}
	if (SIGINT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, ft_handle_ctrl_c);
	}
}

void	ft_handle_ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
