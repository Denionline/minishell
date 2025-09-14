
#include "minishell.h"

// void	signal_handler(void)
// {
// 	if (SIGQUIT)
// 	{
// 		signal(SIGQUIT, SIG_IGN); //ignora o sinal do ctrl + \; ESTA FUNCIONANDO!!
// 	}
// 	if (SIGINT)
// 	{
// 		signal(SIGINT, SIG_IGN); //ignora o sinal do ctrl + c
// 		signal(SIGINT, handle_ctrl_c); 
// 	}
// }

// //ctrl + d sends an EOF, not a signal

// void	handle_ctrl_c(void)
// {
// 	kill(pid, SIGTERM); //kill the process, but ends gracefully as ctrl + c
// 	//return signal of sigterm? ou o kill ja manda o sinal?
// 	//print new line??
// 	//free all from head, but not head
// 	minishell(head);
// }
