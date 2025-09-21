
#include "minishell.h"

int	minishell(t_head *head)
{
	char	*prompt;

	while (1)
	{
//		signal_handler();
		prompt = readline("\001\033[1;92m\002minishell\001\033[1;94m\002> \001\033[0;39m\002");
		if (!prompt)
			break ;
		if (!(*prompt))
			continue ;
		if (!ft_strncmp("exit", prompt, 5))
			break ;
		add_history(prompt);
		parse(head, prompt);
		execute_manager(head);
//		free_all(NULL, head->root, NULL);
		head->root = NULL;
		// print(head->root);
		free(prompt);
//		reset_all(head, prompt);
	}
	return (0);
}
