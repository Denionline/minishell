/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:58:28 by dximenes          #+#    #+#             */
/*   Updated: 2025/10/18 13:03:53 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	heredoc(char *eof)
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
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		if ((!ft_strcmp(line, eof)) || !line)
			break ;
		ft_putstr_fd(line, heredoc_file.fd);
		free(line);
	}
	free(line);
	heredoc_file.exists = TRUE;
	return (heredoc_file);
}
