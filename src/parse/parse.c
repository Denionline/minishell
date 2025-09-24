
#include "minishell.h"

static void	set_fd_file(t_files *files, char *file_name, int operator)
{
	if (operator == DOUBLE_ARROW_RIGHT || operator == ARROW_RIGHT)
	{
		files->out.name = file_name;
		if (operator == DOUBLE_ARROW_RIGHT)
			files->out.flags = O_CREAT | O_WRONLY | O_APPEND;
		else if (operator == ARROW_RIGHT)
			files->out.flags = O_CREAT | O_WRONLY | O_TRUNC;
	}
	else if (operator == ARROW_LEFT)
	{
		files->in.name = file_name;
		files->in.flags = O_RDONLY;
	}
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
	t_parse parse;

	ft_bzero(&parse, sizeof(parse));
	head->paths = get_paths(head->envp);
	while (prompt[parse.pos])
	{
		parse.operator = is_operator(prompt + parse.pos);
		if (!head->root && !parse.operator && !ft_isspace(prompt[parse.pos]))
		{
			parse.command = get_command(head, prompt + parse.pos);
			parse.node_command = btree_create(COMMAND, parse.command, NULL, NULL);
			btree_add_as_first(&head->root, parse.node_command);
		}
		if (parse.operator)
		{
			parse.file_size = 0;
			if (is_arrow_operator(parse.operator))
				arrows_momment(&parse, prompt);
			if (parse.operator != ARROW_RIGHT && parse.operator != DOUBLE_ARROW_RIGHT)
			{
				if (ft_isspace(prompt[parse.file_size + parse.op_size + parse.pos]))
					parse.pos++;
				parse.command = get_command(head, prompt + parse.file_size + parse.op_size + parse.pos);
				parse.node_command = btree_create(COMMAND, parse.command, NULL, NULL);
			}
			if (is_arrow_operator(parse.operator))
			{
				set_fd_file(&parse.node_command->files, parse.file_name, parse.operator);
				btree_add_as_first(&head->root, parse.node_command);
			}
			else
			{
				parse.node_operator = btree_create(
					parse.operator,
					NULL, NULL,
					parse.node_command
				);
				btree_add_as_first(&head->root, parse.node_operator);
			}
			parse.pos += parse.file_size + parse.op_size - 1;
		}
		parse.pos += 1;
	}
}

// < infile cat | grep e > outfile
