
#include "minishell.h"

static int	manage_file(t_file *file, int flags, char *string, t_head *head)
{
	int	complete_size;

	if (head)
	{
		if (flags < 0)
			*file = heredoc(head, string);
		else
		{
			file->name = ft_strdup(string);
			file->flags = flags;
			file->fd = open(file->name, file->flags, 0644);
			close(file->fd);
			file->exists = TRUE;
		}
	}
	complete_size = ft_strlen(string);
	free(string);
	return (complete_size);
}

int	handle_file(t_head *head, t_files *files, char *prompt, int op)
{
	char	*string;
	int		pos;

	if (!files)
		head = NULL;
	pos = get_operator_size(op);
	while (ft_isspace(prompt[pos]))
		pos++;
	string = string_argument(head, prompt + pos,
		(t_arg){.len = &pos, .to_expand = FALSE}
	);
	if (op == ARROW_LEFT)
		return (pos + manage_file(&files->in, O_RDONLY, string, head));
	if (op == DOUBLE_ARROW_LEFT)
		return (pos + manage_file(&files->in, -1, string, head));
	if (op == ARROW_RIGHT)
		return (pos + manage_file(&files->out,
			O_CREAT | O_WRONLY | O_TRUNC, string, head
		));
	if (op == DOUBLE_ARROW_RIGHT)
		return (pos + manage_file(&files->out,
			O_CREAT | O_WRONLY | O_APPEND, string, head
		));
	return (pos);
}
