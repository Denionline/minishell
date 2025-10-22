
#include "minishell.h"

static int	set_file_values(t_file *file, int flags, char *string, char **envp)
{
	int	complete_size;

	if (envp)
	{
		if (flags < 0)
			*file = heredoc(string, envp);
		else
		{
			file->name = ft_strdup(string);
			file->flags = flags;
			file->fd = open(file->name, file->flags, 0644);
			if (file->fd < 0)
				ft_putendl_fd("Erro to open file", 1);
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
	char	**envp;
	int		pos;

	envp = head->env.vars;
	if (!files)
		envp = NULL;
	pos = get_operator_size(op);
	while (ft_isspace(prompt[pos]))
		pos++;
	string = string_argument(prompt + pos, envp, &pos, FALSE);
	if (op == ARROW_LEFT)
		pos += set_file_values(&files->in, O_RDONLY, string, envp);
	else if (op == DOUBLE_ARROW_LEFT)
		pos += set_file_values(&files->in, -1, string, envp);
	else if (op == ARROW_RIGHT)
		pos += set_file_values(&files->out,
			O_CREAT | O_WRONLY | O_TRUNC, string, envp
		);
	else if (op == DOUBLE_ARROW_RIGHT)
		pos += set_file_values(&files->out,
			O_CREAT | O_WRONLY | O_APPEND, string, envp
		);
	return (pos);
}
