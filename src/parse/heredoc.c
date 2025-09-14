
#include "minishell.h"

typedef struct s_heredoc
{
	char	*name;
	char	*eof;
}		t_heredoc;

void	init_struct(t_head *head)
{
	t_heredoc	*heredoc;

	heredoc = malloc(sizeof(t_heredoc));
	if (!heredoc)
		//free_function
	heredoc->eof = parse_eof; //precisa ser feito parse_eof
	fd_heredoc(heredoc);
	heredoc->fd_in = open("tmp_heredoc", O_RDONLY);
	if (heredoc->fd_in == -1)
		//free_function
	//nao sei se ja daria para abrir o fd_out aqui, ou precisa ser no ultimo processo
	heredoc->fd_out = open(head->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644); //precisa criar o char *outfile no head
	if (fd_out == -1)
		//free_function
	//mas acho que da para armazenar aqui e fazer o dup2 la no ultimo processo depois
}

void	fd_heredoc(t_heredoc *heredoc)
{
	int		fd;
	char	*line;
	char	*eof;

	fd = open("tmp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		//free_function
	while (1)
	{
		ft_putstr_fd(heredoc->name, 1);
		line = get_next_line(STDIN_FILENO);
		if ((ft_strncmp(line, heredoc->eof, ft_strlen(line))) == 0 || !line)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
}
