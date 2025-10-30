
#include "minishell.h"

int	minishell(t_head *head)
{
	char	*prompt;

	while (1)
	{
//		signal_handler();
		prompt = readline("\001\033[1;92m\002minishell\001\033[1;94m\002> \001\033[0;39m\002");
		if (!prompt && ft_putendl_fd("exit", 1))
			break ;
		if (!ft_strncmp("exit", prompt, 5))
		{
			ft_exit(head);
			break ;
		}
		if (!(*prompt))
			continue ;
		add_history(prompt);
		parse(head, prompt);
		execute_manager(head);
//		print(head->root);
		head->root = NULL;
	}
	return (0);
}
