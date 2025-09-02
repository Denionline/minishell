
#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_head	*head;

	initializer(&head, argc, argv, envp);
	minishell(head);
	// end(head, 0, "SUCESS");
}
