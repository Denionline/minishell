
#include "minishell.h"

static char	**realloc_args(char **old_args, int new_len)
{
	char	**new_args;
	int		i;

	new_args = ft_calloc(new_len + 1, sizeof(char *));
	if (!new_args)
		return (NULL);
	if (old_args)
	{
		i = 0;
		while (old_args[i])
		{
			new_args[i] = old_args[i];
			i++;
		}
		free(old_args);
	}
	return (new_args);
}

static char	**get_cmd_args(char *prompt)
{
	char		**args;
	int			size_args;
	int			operator;
	int			i;

	if (!prompt || !*prompt)
		return (NULL);
	args = NULL;
	size_args = 0;
	i = 0;
	while (prompt[i])
	{
		operator = is_operator(prompt + i);
		if (operator == DOUBLE_ARROW_RIGHT || operator == ARROW_RIGHT)
			prompt += get_next_increase(operator);
		else if (operator)
			break ;
		if (!ft_isspace(prompt[i]) && (i == 0 || ft_isspace(prompt[i - 1])))
		{
			args = realloc_args(args, size_args + 1);
			args[size_args] = get_string_argument(prompt + i);
			prompt += ft_strlen(args[size_args++]);
			i = 0;
		}
		i++;
	}
	return (args);
}

t_cmd	*get_command(t_head *head, char *prompt)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = get_cmd_args(prompt);
	if (!cmd->args)
		return (NULL);
	cmd->path = get_valid_path(head->paths, cmd->args[0]);
	if (!cmd->path)
		return (NULL);
	return (cmd);
}
