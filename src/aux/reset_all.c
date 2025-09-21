
#include "minishell.h"

void	reset_all(t_head *head, char *prompt)
{
	int	i;

	i = 0;
	if (head->root)
		free_all(NULL, head->root, NULL);
	head->root = NULL;
	free(head->pid);
	free(prompt);
}
