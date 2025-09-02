
#include "minishell.h"

// static t_cmd	get_command(t_head *head)
// {
// 	(void)head;
// }

void	parse(t_head *head, char *prompt)
{
	char	**values;
	int		i;

	values = ft_split(prompt, ' ');
	head->cmds = malloc(sizeof(t_cmd) * get_array_len(values));
	if (!head->cmds)
		end(head, errno, "head->cmds");
	i = 0;
	while (values[i])
	{
		// get_command(head);
		i++;
	}
}
