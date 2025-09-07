
#include "minishell.h"

static int	get_size_args(char **values)
{
	int	i;

	i = 0;
	while (values[i] && !is_signal(values[i]))
	{
		i++;
	}
	return (i);
}

static t_cmd	get_command(t_head *head, char **values, int *pos)
{
	t_cmd	command;
	int		i;

	command.args = malloc(sizeof(char *) * get_size_args(values) + 1);
	if (!command.args)
		end(head, errno, "command.args");
	i = 0;
	while (values[*pos] && !is_signal(values[*pos]))
	{
		command.args[i++] = values[*pos];
		(*pos)++;
	}
	command.args[i] = NULL;
	if (values[*pos] && is_signal(values[*pos]))
		command.right_sig = values[(*pos)++];
	return (command);
}

void	parse(t_head *head, char *prompt)
{
	char	**values;
	int		array_len;
	int		pos;
	int		i;

	values = ft_split(prompt, ' ');
	array_len = get_array_len(values);
	head->cmds = malloc(sizeof(t_cmd) * (array_len + 1));
	if (!head->cmds)
		end(head, errno, "head->cmds");
	pos = 0;
	i = 0;
	while (i < array_len)
	{
		head->cmds[i] = get_command(head, values, &pos);
		i++;
	}
}
