#include "minishell.h"

void	stop_heredoc(t_file *hdoc)
{
	unlink(hdoc->name);
	define_exit_code(130, TRUE);
}

static void	get_lines(t_head *head, t_file *hdoc, char *eof)
{
	char	*line;

	while (TRUE)
	{
		if (SIGINT)
		{
			signal(SIGINT, ft_ctrl_c_heredoc);
			stop_heredoc(hdoc);
		}
		line = readline("> ");
		if ((!line || !ft_strncmp(line, eof, ft_strlen(eof))))
			break ;
		line = string_argument(head, line, (t_arg){.to_expand = TRUE});
		ft_putstr_fd(line, hdoc->fd);
		ft_putstr_fd("\n", hdoc->fd);
		free(line);

	}
	free(line);
}

t_file	heredoc(t_head *head, char *eof)
{
	t_file	heredoc_file;
	char	*idx;
	int		save_stdin;

	idx = ft_itoa(head->n_cmds);
	heredoc_file.name = ft_strjoin(".heredoc_", idx);
	free(idx);
	heredoc_file.flags = O_CREAT | O_RDWR;
	heredoc_file.fd = open(heredoc_file.name, heredoc_file.flags, 0644);
	if (heredoc_file.fd == -1)
		return (free(heredoc_file.name), (t_file){.exists = FALSE});
	save_stdin = dup(STDIN_FILENO);
	get_lines(head, &heredoc_file, eof);
	dup2(save_stdin, STDIN_FILENO);
	close(heredoc_file.fd);
	// if (define_exit_code(0, FALSE) == 130)
	// 	//precisa parar a criacao da arvore aqui - nada continuah
	// else
	heredoc_file.exists = TRUE;
	return (heredoc_file);
}
