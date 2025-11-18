#include "minishell.h"

static void	get_lines(t_head *head, t_file *hdoc, char *eof)
{
	const int	leof = ft_strlen(eof);
	char		*line;

	while (TRUE)
	{
		signal(SIGINT, ft_ctrl_c_heredoc);
		line = readline("> ");
		if ((!line || !ft_strncmp(line, eof, leof)))
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

	heredoc_file = (t_file){};
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
	close(save_stdin);
	close(heredoc_file.fd);
	heredoc_file.exists = TRUE;
	heredoc_file.operator = DOUBLE_ARROW_LEFT;
	if (define_exit_code(0, FALSE) == 130)
	{
		head->to_stop = TRUE;
		free(heredoc_file.name);
	}
	return (heredoc_file);
}
