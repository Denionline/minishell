/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:58:28 by dximenes          #+#    #+#             */
/*   Updated: 2025/10/19 11:27:11 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*quote_string(char *string)
{
	char	*string_left_quoted;
	char	*string_right_quoted;

	string_left_quoted = ft_strjoin("\"", string);
	free(string);
	string_right_quoted = ft_strjoin(string_right_quoted, "\"");
	free(string_left_quoted);
	return (string_right_quoted);
}

t_file	heredoc(char *eof, char **envp)
{
	t_file	heredoc_file;
	char	*line;

	heredoc_file.name = ft_strjoin(".heredoc_", eof);
	heredoc_file.flags = O_CREAT | O_RDWR;
	heredoc_file.fd = open(heredoc_file.name, heredoc_file.flags, 0644);
	if (heredoc_file.fd == -1)
		return (free(heredoc_file.name), (t_file){.exists = FALSE});
	while (TRUE)
	{
		// ft_putstr_fd("> ", 1);
		line = readline("> ");
		if ((!ft_strncmp(eof, line, ft_strlen(eof))) || !line)
			break ;
		line = quote_string(line);
		line = string_argument(line, envp, NULL, TRUE);
		ft_putstr_fd(line, heredoc_file.fd);
		ft_putstr_fd("\n", heredoc_file.fd);
		free(line);
	}
	free(line);
	close(heredoc_file.fd);
	heredoc_file.exists = TRUE;
	return (heredoc_file);
}
