
#include "minishell.h"

static void	reset_files(t_files *files)
{
	ft_bzero(files, sizeof(*files));
	files->in.fd = -1;
	files->out.fd = -1;
}

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

	cmd = get_command(head, prompt);
	if (!cmd)
		return ;
	node_command = btree_create(COMMAND, cmd, NULL, NULL);
	if (op)
		btree_add_as_first(&head->root,
			btree_create(op, NULL, NULL, node_command)
		);
	else
		btree_add_as_first(&head->root,
			node_command
		);
}

static int	handle_operator(t_head *head, char *prompt, int op, t_files *files)
{
	int		pos;

	if (is_arrow_operator(op))
		return (handle_file(files, prompt, op, TRUE));
	pos = get_operator_size(op);
	while (ft_isspace(prompt[pos]))
		pos++;
	add_node_on_tree(head, op, prompt + pos);
	if (is_file_pending(files))
		btree_set_file_last_cmd(&head->root, (*files));
	reset_files(files);
	return (pos);
}

static void	handle_first_command(t_head *head, char *prompt, t_files *files)
{
	if (!head->root)
		add_node_on_tree(head, 0, prompt);
	if (is_file_pending(files))
		btree_set_file_last_cmd(&head->root, (*files));
	reset_files(files);
}

static void	arrows_momment(t_parse *parse, char *prompt)
{
	if (ft_isspace(prompt[parse->pos]))
		parse->pos++;
	parse->op_size = get_next_increase(parse->operator);
	if (ft_isspace(prompt[parse->op_size + parse->pos]))
		parse->pos++;
	parse->file_name = get_string_argument(prompt + parse->op_size + parse->pos);
	parse->file_size = ft_strlen(parse->file_name);
	if (parse->file_name[0] == '\'' || parse->file_name[0] == '\"')
		parse->file_name = ft_strremove(parse->file_name, parse->file_name[0]);
}

void	parse(t_head *head, char *prompt)
{
	t_files	files;
	int		operator;
	int		i;
	
	head->paths = get_paths(head->envp);
	reset_files(&files);
	i = 0;
	while (prompt[i])
	{
		operator = get_operator(prompt + i);
		if (operator)
			i += handle_operator(head, prompt + i, operator, &files);
		if (!head->root || is_file_pending(&files))
			handle_first_command(head, prompt + i, &files);
		while (!ft_isspace(prompt[i]))
			i++;
		i += !operator;
	}
}
