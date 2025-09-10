
#include "minishell.h"

int	minishell(t_head *head)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("\001\033[1;92m\002minishell\001\033[1;94m\002> \001\033[0;39m\002");
		if (!ft_strncmp("exit", prompt, 5))
			break ;
		parse(head, prompt);
		hierarchy(head);
	}
	return (0);
}
