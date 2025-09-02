
#include "minishell.h"

void	initializer(t_head **head, int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(*head) = malloc(sizeof(t_head));
	if (!(*head))
		end(*head, errno, "head");
	ft_bzero(*head, sizeof(**head));
	(*head)->envp = envp;
}