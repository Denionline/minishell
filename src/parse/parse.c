
#include "minishell.h"

static void	reset_files(t_files *files)
{
	ft_bzero(files, sizeof(*files));
	files->in.fd = -1;
	files->out.fd = -1;
}

static int	out_pending(t_files *files)
{
	if (files->out.exists)
		return (TRUE);
	return (FALSE);
}

static int	in_pending(t_files *files)
{
	if (files->in.exists)
		return (TRUE);
	return (FALSE);
}

static int	handle_operator(t_head *head, char *prompt, int op, t_files *files)
{
	t_btree	*node_command;
	int		pos;

	if (is_arrow_operator(op))
		return (handle_file(files, prompt, op, TRUE));
	pos = get_operator_size(op);
	while (ft_isspace(prompt[pos]))
		pos++;
	node_command = btree_create(COMMAND,
		get_command(head, prompt + pos), NULL, NULL
	);
	if (in_pending(files))
		node_command->files = (*files);
	btree_add_as_first(&head->root,
		btree_create(op, NULL, NULL, node_command)
	);
	reset_files(files);
	return (pos);
}

static void	handle_first_command(t_head *head, char *prompt, t_files *files)
{
	t_btree	*node_command;

	if (out_pending(files))
		btree_set_file_last_cmd(&head->root, (*files));
	else if (in_pending(files))
		btree_set_file_last_cmd(&head->root, (*files));
	else
	{
		node_command = btree_create(COMMAND,
			get_command(head, prompt), NULL, NULL
		);
		if (in_pending(files))
			node_command->files = (*files);
		btree_add_as_first(&head->root,
			node_command
		);
	}
	reset_files(files);
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
		if (!ft_isspace(prompt[i]))
			if (!head->root || in_pending(&files) || out_pending(&files))
				handle_first_command(head, prompt + i, &files);
		i += !operator;
	}
}
