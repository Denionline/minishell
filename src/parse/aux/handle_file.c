
#include "minishell.h"

static int	manage_file(t_file **file, t_head *head, char *string, t_file data)
{
	int	complete_size;

	if (data.exists)
	{
		if (data.flags < 0)
			(*file)[0] = heredoc(head, string);
		else
			(*file)[0] = (t_file){
				.name = ft_strdup(string),
				.flags = data.flags,
				.exists = TRUE,
				.fd = -1,
				// .fd = open(file->name, file->flags, 0644),
			};
		// if ((*file)->fd == -1)
		// 	close((*file)->fd);
	}
	complete_size = ft_strlen(string);
	free(string);
	return (complete_size);
}

static int	get_flags(int op)
{
	if (op == ARROW_LEFT)
		return (O_RDONLY);
	if (op == DOUBLE_ARROW_LEFT)
		return (-1);
	if (op == ARROW_RIGHT)
		return (O_CREAT | O_WRONLY | O_TRUNC);
	if (op == DOUBLE_ARROW_RIGHT)
		return (O_CREAT | O_WRONLY | O_APPEND);
	return (0);
}

int	handle_file(t_head *head, t_files *files, char *prompt, int op)
{
	t_file	data;
	char	*string;
	int		pos;

	data = (t_file){ .flags = get_flags(op) , .exists = !(!files)};
	pos = get_operator_size(op);
	while (ft_isspace(prompt[pos]))
		pos++;
	string = string_argument(head, prompt + pos,
		(t_arg){.len = &pos, .to_expand = FALSE}
	);
	if (op == ARROW_LEFT)
		return (pos + manage_file(&files->in, head, string, data));
	if (op == DOUBLE_ARROW_LEFT)
		return (pos + manage_file(&files->in, head, string, data));
	if (op == ARROW_RIGHT)
		return (pos + manage_file(&files->out, head, string, data));
	if (op == DOUBLE_ARROW_RIGHT)
		return (pos + manage_file(&files->out, head, string, data));
	return (pos);
}
