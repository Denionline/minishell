
#include "minishell.h"

static t_cmd	*get_command(t_head *head, char *prompt)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = get_args(prompt);
	printf("%s\n", cmd->args[0]);
	cmd->path = get_valid_path(head->paths, cmd->args[0]);
	return (cmd);
}

static char	*get_signal(char *prompt, int len)
{
	char	*signal;
	int		i;

	signal = ft_calloc(1, len + 1);
	if (!signal)
		return (NULL);
	i = 0;
	while (i < len)
	{
		signal[i] = prompt[i];
		i++;
	}
	signal[i] = '\0';
	return (signal);
}

// ls -l | echo "hello world" && cat
void	parse(t_head *head, char *prompt)
{
	const int	len = ft_strlen(prompt);
	t_token		*token_operator;
	t_token		*token_command;
	int			operator_size;
	int			pos;
	int			i;

	head->paths = get_paths(head->envp);
	i = 0;
	while (prompt[i])
	{
		pos = len - i;
		operator_size = is_operator(prompt + pos);
		if (operator_size > 0)
		{
			pos++;
			token_command = btree_create("cmd",
				get_command(head, prompt + pos),
				NULL, NULL);
			token_operator = btree_create(
					get_signal(prompt + pos - operator_size, operator_size),
					NULL, NULL,	token_command);
			btree_add_last_left(&head->tokens, token_operator);
			i += operator_size;
		}
		else
			i += 1;
	}
}
