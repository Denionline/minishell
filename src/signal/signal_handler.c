
#include "minishell.h"

void	signal_handler(void)
{
	if (SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
	}
/*	if (SIGINT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGINT, ft_handle_ctrl_c); 
	}*/
}

void	ft_handle_ctrl_c(int sig)
{
	//free all from head, but not head
	//exit_status = 130; //tem que liberar esse sinal, que e SIGINT
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line(); //para readline descer linha
	rl_replace_line("", 0); //replace the input line with nothing
	rl_redisplay(); //redraw input and input line
}
