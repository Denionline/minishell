
#include "minishell.h"

static int	is_file_pending(t_files *files)
{
	if (files->in.exists)
		return (TRUE);
	if (files->out.exists)
		return (TRUE);
	return (FALSE);
}

static void	add_node_on_tree(t_head *head, int op, char *prompt)
{
	t_btree	*node_command;
	t_cmd	*cmd;

	head->n_cmds += 1;
	cmd = get_command(head, prompt);
	node_command = btree_create(COMMAND, cmd, NULL, NULL);
	if (op)
		btree_add_as_first(&head->root,
			btree_create(op, NULL, NULL, node_command)
		);
	else
		btree_add_as_first(&head->root, node_command);
}

static int	handle_operator(t_head *head, char *prompt, int op, t_files *files)
{
	int	pos;

	pos = get_operator_size(op);
	while (ft_isspace(prompt[pos]))
		pos++;
	if (!is_valid_argument(prompt + pos, &op))
		ft_exit(head, NULL);
	if (is_arrow_operator(op))
		return (pos + handle_file(head, files, prompt, op));
	add_node_on_tree(head, op, prompt + pos);
	if (is_file_pending(files))
		btree_set_file_last_cmd(&head->root, &files);
	return (pos);
}

static void	handle_first_command(t_head *head, char *prompt, t_files *files)
{
	if (!head->root)
		add_node_on_tree(head, 0, prompt);
	if (is_file_pending(files))
		btree_set_file_last_cmd(&head->root, &files);
}

void	parse(t_head *head, char *prompt)
{
	t_files	files;
	int		operator;
	int		i;
	
	files = (t_files){.in.fd = -1, .out.fd = -1};
	i = 0;
	while (prompt[i])
	{
		head->cmd_size = 0;
		operator = get_operator(prompt + i);
		if (operator)
			i += handle_operator(head, prompt + i, operator, &files);
		if (!head->root || is_file_pending(&files))
			handle_first_command(head, prompt + i, &files);
		i += head->cmd_size + (!head->cmd_size && !operator);
	}
}

// "/bin/echo hello"
