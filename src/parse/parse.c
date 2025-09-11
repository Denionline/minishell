
#include "minishell.h"

static int	get_size_string_command(char *string)
{
	int		i;
	
	i = 0;
	while (string[i] && !is_operator(string + i))
		i++;
	return (i);
}

static char	*get_string_command(char *string_command)
{
	const int	string_size = get_size_string_command(string_command);
	char		*string;
	int			i;

	string = ft_calloc(1, string_size + 1);
	if (!string)
		return (NULL);
	i = 0;
	while (string_command[i] && !is_operator(string_command + i))
	{
		string[i] = string_command[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

static char	*get_command(t_head *head, char *prompt)
{
	char	*string_command;
	t_cmd	*cmd;

	
	string_command = get_string_command(prompt);
	cmd->args = ft_strtok(string_command, "\'\"");
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
				get_command(head, prompt),
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
