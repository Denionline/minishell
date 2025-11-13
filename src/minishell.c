#include "minishell.h"

int	minishell(t_head *head)
{
	char	*prompt;

	while (1)
	{
		signal_handler();
		prompt = readline("\001\033[1;92m\002minishell\001\033[1;94m\002> \001\033[0;39m\002");
		if (!prompt)
			ft_exit(head, NULL);
		if (!(*prompt))
			continue ;
		add_history(prompt);
		parse(head, prompt);
		execute_manager(head);
		head->exit_code = define_exit_code(0, FALSE);
		// print(head);
	}
	return (0);
}
