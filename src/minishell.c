#include "minishell.h"

int	minishell(t_head *head)
{
	char	*prompt;
	char	prompt_prefix[10000];

	while (TRUE)
	{
		signal_handler();
		get_prompt_prefix(prompt_prefix);
		prompt = readline(prompt_prefix);
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
