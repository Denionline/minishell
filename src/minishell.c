#include "minishell.h"

int	minishell(t_head *head)
{
	char	preprompt[9999];
	char	*prompt;

	while (TRUE)
	{
		signal_handler();
		prompt_prefix(preprompt);
		prompt = readline(preprompt);
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
