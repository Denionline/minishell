
#include "minishell.h"

static int	set_file_values(t_file *file, int flags, char *prompt, int to_change)
{
	char	*string_argument;
	int		complete_size;

	string_argument = get_string_argument(prompt);
	if (to_change)
	{
		file->exists = TRUE;
		file->flags = flags;
		file->name = ft_strdup(string_argument);
		if (file->name[0] == '\'' || file->name[0] == '\"')
			file->name = ft_strremove(file->name, file->name[0]);
	}
	complete_size = ft_strlen(string_argument);
	free(string_argument);
	return (complete_size);
}

int	handle_file(t_files *files, char *prompt, int op, int to_change)
{
	int	pos;

	pos = get_operator_size(op);
	while (ft_isspace(prompt[pos]))
		pos++;
	if (op == ARROW_LEFT)
		pos += set_file_values(&files->in,
			O_RDONLY, prompt + pos, to_change
		);
	else if (op == DOUBLE_ARROW_LEFT)
		pos += set_file_values(&files->in,
			-1, prompt + pos, to_change
		);
	else if (op == ARROW_RIGHT)
		pos += set_file_values(&files->out,
			O_CREAT | O_WRONLY | O_TRUNC, prompt + pos, to_change
		);
	else if (op == DOUBLE_ARROW_RIGHT)
		pos += set_file_values(&files->out,
			O_CREAT | O_WRONLY | O_APPEND, prompt + pos, to_change
		);
	return (pos);
}
