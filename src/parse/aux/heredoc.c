/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:09:57 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/22 12:50:29 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_random_name(int size)
{
	char	string[size];
	int		fd;
	int		i;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		return (NULL);
	read(fd, string, size);
	close(fd);
	i = 0;
	string[i++] = '.';
	string[i++] = '\"';
	while (i < size)
	{
		if (!ft_isprint(string[i]))
			string[i] = 'o';
		i += 1;
	}
	string[size - 2] = '\"';
	string[size - 1] = '\0';
	return (ft_strdup(string));
}

static void	get_lines(t_head *head, t_file *hdoc, char *eof)
{
	char	*line;

	hdoc->is_there_heredoc = TRUE;
	while (TRUE)
	{
		signal(SIGINT, ft_ctrl_c_heredoc);
		line = readline("> ");
		if (!line || is_strmatch(line, eof) || (!(*eof) && !(*line)))
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
	int		save_stdin;

	heredoc_file = (t_file){.flags = O_CREAT | O_RDWR};
	heredoc_file.name = get_random_name(20);
	heredoc_file.fd = open(heredoc_file.name, heredoc_file.flags, 0644);
	if (heredoc_file.fd == -1)
		return (free(heredoc_file.name), (t_file){.exists = FALSE});
	save_stdin = dup(STDIN_FILENO);
	define_exit_code(0, TRUE);
	get_lines(head, &heredoc_file, eof);
	signal_handler();
	dup2(save_stdin, STDIN_FILENO);
	close(save_stdin);
	close(heredoc_file.fd);
	if (define_exit_code(0, FALSE) == 130)
	{
		head->to_stop = TRUE;
		unlink(heredoc_file.name);
		free(heredoc_file.name);
	}
	return (heredoc_file);
}
