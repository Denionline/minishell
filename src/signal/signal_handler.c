#include "minishell.h"

void	ft_handle_ctrl_c_child(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	signal_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_handle_ctrl_c);
	signal(SIGPIPE, SIG_IGN);
}

// void	signal_handler(t_head *head, int process)
// {
// 	(void)*head;
// 	if (SIGQUIT)
// 	{
// 		signal(SIGQUIT, SIG_IGN);
// 	}
// 	if (SIGINT)
// 	{
// 		if (process == 1)
// 		{
// 			signal(SIGINT, SIG_IGN);
// 			signal(SIGINT, ft_handle_ctrl_c);
// 			//head->exit_code = 130;
// 		}
// 		else if (process == 0)
// 		{
// 			signal(SIGINT, SIG_DFL);
// 			signal(SIGINT, ft_handle_ctrl_c_child);
// 		}
// 	}
// }

void	ft_handle_ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	define_exit_code(130, TRUE);
}



void	child_signal_handler(void)
{
	if (SIGINT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, ft_handle_ctrl_c_child);
	}
}