#include "minishell.h"

int	minishell(t_head *head)
{
	char	*prompt;

	while (TRUE)
	{
		signal_handler();
		prompt = readline(BOLD C_GREEN"minishell"C_MAGENTA"> "RESET);
		if (!prompt)
			ft_exit(head, NULL);
		if (!(*prompt))
			continue ;
		add_history(prompt);
		parse(head, prompt);
		execute_manager(head);
	}
	return (0);
}
