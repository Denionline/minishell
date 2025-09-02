
#include "minishell.h"

static void	show_error(int error, char *description)
{
	printf("[SHELL]: %s: %s\n", strerror(error), description);
}

int	end(t_head *head, int status, char *description)
{
	if (status != 0)
		show_error(status, description);
	if (head)
	{
		free(head);
	}
	exit(status);
}
