
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

static char	*get_operator(char *prompt, int len)
{
	char	*operator;
	int		i;

	operator = ft_calloc(1, len + 1);
	if (!operator)
		return (NULL);
	i = 0;
	while (i < len)
	{
		operator[i] = prompt[i];
		i++;
	}
	operator[i] = '\0';
	return (operator);
}

void	parse(t_head *head, char *prompt)
{
	const int	len = ft_strlen(prompt);
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
			btree_add_last_left(&head->root,
				btree_create(
					get_operator(prompt + pos - operator_size, operator_size),
					NULL, NULL,
					btree_create(ft_strdup("cmd"),
						get_command(head, prompt + pos),
						NULL, NULL
					)
				)
			);
			i += operator_size;
			}
			else
				i += 1;
		}
	btree_add_last_left(&head->root,
		btree_create(ft_strdup("cmd"),
			get_command(head, prompt),
			NULL, NULL)
	);
}
