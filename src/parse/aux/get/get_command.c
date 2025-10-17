
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

static void	set_cmd_args(t_head *head, t_cmd *cmd, char *prompt)
{
	int	size_args;
	int	op;
	int	i;

	if (!prompt || !*prompt)
		return ;
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
			cmd->args = realloc_args(cmd->args, size_args + 1);
			cmd->args[size_args++] = string_argument(prompt + i, head->envp, &i);
			prompt += i;
			i = 0;
			continue;
		}
		i++;
	}
}

t_cmd	*get_command(t_head *head, char *prompt)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	set_cmd_args(head, cmd, prompt);
	if (!cmd->args)
		return (NULL);
	cmd->path = get_valid_path(head->paths, cmd->args[0]);
	if (!cmd->path)
		return (NULL);
	return (cmd);
}


// echo hello > outfile world > outfile1 ne
