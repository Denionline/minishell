
#include "minishell.h"

static t_cmd	*get_command(t_head *head, char *prompt)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = get_cmd_args(prompt);
	cmd->path = get_valid_path(head->paths, cmd->args[0]);
	return (cmd);
}

void	parse(t_head *head, char *prompt)
{
	const int	len = ft_strlen(prompt);
	int			operator;
	int			pos;
	int			i;

	head->paths = get_paths(head->envp);
	i = 0;
	while (prompt[i])
	{
		pos = len - i;
		operator = is_operator(prompt + pos);
		if (operator > 0)
		{
			pos++;
			btree_add_last_left(&head->root,
				btree_create(
					operator,
					NULL, NULL,
					btree_create(COMMAND,
						get_command(head, prompt + pos),
						NULL, NULL
					)
				)
			);
		}
		else
			i += 1;
	}
	btree_add_last_left(&head->root,
		btree_create(COMMAND,
			get_command(head, prompt),
			NULL, NULL)
	);
}
