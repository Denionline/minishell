
#include "minishell.h"

static void	handle_command_arguments(t_head *head, t_cmd *cmd, char *prompt)
{
	int	size_args;
	int	op;
	int	i;

	size_args = 0;
	i = 0;
	while (prompt[i])
	{
		op = get_operator(prompt + i);
		if (is_arrow_operator(op))
			prompt += handle_file(head, 0, prompt + i, op);
		else if (op)
			break ;
		if (!ft_isspace(prompt[i]) && (i == 0 || ft_isspace(prompt[i - 1])))
		{
			cmd->args = get_realloc_args(cmd->args, ++size_args,
				string_argument(head, prompt + i,
					(t_arg){.len = &i, .to_expand = TRUE}
				)
			);
			prompt += i - 1;
			i = 0;
		}
		i += !op;
	}
}

t_cmd	*get_command(t_head *head, char *prompt)
{
	t_cmd	*command;

	command = ft_calloc(1, sizeof(t_cmd));
	if (!command)
		return (NULL);
	handle_command_arguments(head, command, prompt);
	command->path = NULL;
	if (command->args)
		command->path = get_valid_path(&head->env, command->args[0]);
	return (command);
}
