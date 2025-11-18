
#include "minishell.h"

static int	is_file_pending(t_head *head, t_files *files)
{
	if (head->to_stop)
		return (FALSE);
	if (files->in.exists)
		return (TRUE);
	if (files->out.exists)
		return (TRUE);
	return (FALSE);
}

static void	add_node_on_tree(t_head *head, int op, char *str, t_files *files)
{
	t_btree	*node_command;
	t_cmd	*cmd;

	head->n_cmds += 1;
	cmd = get_command(head, str, files);
	if (!cmd)
		return ;
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
	if (!is_valid_argument(head, prompt + pos, op, get_operator(prompt + pos)))
	{
		head->to_stop = TRUE;
		ft_error(head, (t_error){.id = ERR_SYNTAX_ERROR});
		return (-1);
	}
	if (is_arrow_operator(op))
		return (handle_file(head, 0, prompt, op));
	add_node_on_tree(head, op, prompt + pos, files);
	if (is_file_pending(head, files))
		btree_set_file_last_cmd(&head->root, &files);
	return (pos);
}

static int	handle_command(t_head *head, int op, char *prompt, t_files *files)
{
	int	pos;

	pos = get_operator_size(op);
	while (ft_isspace(prompt[pos]))
		pos++;
	if (!is_valid_argument(head, prompt + pos, op, get_operator(prompt + pos)))
	{
		head->to_stop = TRUE;
		ft_error(head, (t_error){.id = ERR_SYNTAX_ERROR});
		return (-1);
	}
	if (!head->root)
		add_node_on_tree(head, 0, prompt, files);
	if (is_file_pending(head, files))
		btree_set_file_last_cmd(&head->root, &files);
	return (0);
}

void	parse(t_head *head, char *prompt)
{
	t_files	files;
	int		operator;
	int		next;
	int		i;

	if (!is_quotes_valid(prompt))
		return (ft_error(head, (t_error){.id = ERR_QUOTES_ERROR}));
	files = (t_files){.in.fd = -1, .out.fd = -1};
	head->to_stop = FALSE;
	i = 0;
	while (prompt[i])
	{
		head->cmd_size = 0;
		next = 0;
		operator = get_operator(prompt + i);
		if (head->root && operator)
			next = handle_operator(head, prompt + i, operator, &files);
		else if (!head->root || is_file_pending(head, &files))
			next = handle_command(head, operator, prompt + i, &files);
		if (next < 0 || head->to_stop)
			break ;
		i += next + head->cmd_size;
		i += (!head->cmd_size && !operator);
	}
}
