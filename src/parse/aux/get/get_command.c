#include "minishell.h"

static void	handle_command_arguments(t_head *head, t_cmd *cmd, char *prompt, t_files *files)
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
			i += handle_file(head, files, prompt + i, op);
		else if (op)
			break ;
		else if (!ft_isspace(prompt[i])
			&& (i == 0 || ft_isspace(prompt[i - 1])))
		{
			cmd->args = get_realloc_args(cmd->args, ++size_args,
					string_argument(head, prompt + i,
						(t_arg){.len = &i, .to_expand = TRUE}));
			head->cmd_size += i;
			prompt += i;
			i = 0 - !op;
		}
		i += !op;
	}
}

t_cmd	*get_command(t_head *head, char *prompt, t_files *files)
{
	t_cmd	*command;

	command = ft_calloc(1, sizeof(t_cmd));
	if (!command)
		return (NULL);
	handle_command_arguments(head, command, prompt, files);
	command->path = NULL;
	if (command->args)
		command->path = get_valid_path(&head->env, command->args[0]);
	return (command);
}
