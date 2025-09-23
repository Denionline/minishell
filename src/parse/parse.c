
#include "minishell.h"

static t_cmd	*get_command(t_head *head, char *prompt)
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

static void	set_fd_file(t_btree *node, char *prompt, int operator, int file_size)
{
	char	*file_name;

	file_name = get_file_name(prompt, operator_size(operator), file_size);
	if (!file_name)
		return ;
	if (operator == DOUBLE_ARROW_RIGHT)
		node->fd.out = open(file_name, O_CREAT | O_WRONLY | O_APPEND);
	else if (operator == ARROW_RIGHT)
		node->fd.out = open(file_name, O_CREAT | O_WRONLY | O_TRUNC);
	else if (operator == ARROW_LEFT)
		node->fd.in = open(file_name, O_RDONLY);
}

void	parse(t_head *head, char *prompt)
{
	t_btree		*node_operator;
	t_btree		*node_command;
	t_cmd		*command;
	int			operator;
	int			op_size;
	int			i;

	head->paths = get_paths(head->envp);
	i = 0;
	while (prompt[i])
	{
		operator = is_operator(prompt + i);
		if (!head->root && !operator && !ft_isspace(prompt[i]))
		{
			node_command = btree_create(COMMAND,
				get_command(head, prompt + i),
				NULL, NULL
			);
			btree_add_as_first(&head->root, node_command);
		}
		if (operator)
		{
			node_command = NULL;
			op_size = get_next_increase(operator, prompt + i);
			if (operator != ARROW_RIGHT && operator != DOUBLE_ARROW_RIGHT)
			{
				command = get_command(head, prompt + op_size + i);
				if (command != NULL)
					node_command = btree_create(COMMAND, command, NULL, NULL);
			}
			node_operator = btree_create(
				operator,
				NULL, NULL,
				node_command
			);
			if (operator == ARROW_LEFT || operator == ARROW_RIGHT || operator == DOUBLE_ARROW_RIGHT)
				set_fd_file(node_operator, prompt + i, operator, op_size);
			btree_add_as_first(&head->root, node_operator);
			i += op_size - 1;
		}
		i += 1;
	}
}

// < infile cat | grep e > outfile
