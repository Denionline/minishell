
#include "minishell.h"

static int	set_file_values(t_file *file, int flags, char *string, int to_change)
{
	int	complete_size;

	if (to_change)
	{
		if (flags < 0)
			*file = heredoc(string);
		else
		{
			file->exists = TRUE;
			file->flags = flags;
			file->name = ft_strdup(string);
		}
	}
	complete_size = ft_strlen(string);
	free(string);
	return (complete_size);
}

int	handle_file(t_head *head, t_files *files, char *prompt, int op)
{
	char	*string;
	int		to_change;
	int		pos;

	to_change = TRUE;
	if (!files)
		to_change = FALSE;
	pos = get_operator_size(op);
	while (ft_isspace(prompt[pos]))
		pos++;
	string = string_argument(prompt + pos, head->envp, NULL);
	if (op == ARROW_LEFT)
		pos += set_file_values(&files->in,
			O_RDONLY, string, to_change
		);
	else if (op == DOUBLE_ARROW_LEFT)
		pos += set_file_values(&files->in,
			-1, string, to_change
		);
	else if (op == ARROW_RIGHT)
		pos += set_file_values(&files->out,
			O_CREAT | O_WRONLY | O_TRUNC, string, to_change
		);
	else if (op == DOUBLE_ARROW_RIGHT)
		pos += set_file_values(&files->out,
			O_CREAT | O_WRONLY | O_APPEND, string, to_change
		);
	return (pos);
}
