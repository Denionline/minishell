/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:58:28 by dximenes          #+#    #+#             */
/*   Updated: 2025/10/31 14:37:59 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_idx(t_btree *node)
{
	t_file	*files;
	int		i;

	if (node->right->identifier)
		files = node->right->files.in;
	else
		files = node->files.in;
	i = 0;
	while (files[i].exists)
		i++;
	return (i);
}

static void	get_lines(t_head *head, t_file *hdoc, char *eof)
{
	char	*line;

	while (TRUE)
	{
		line = readline("> ");
		if ((!line || !ft_strncmp(eof, line, ft_strlen(eof))))
			break ;
		line = string_argument(head, line,
			(t_arg){.to_expand = TRUE}
		);
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

	idx = ft_itoa(get_idx(head->root));
	heredoc_file.name = ft_strjoin(".heredoc_", idx);
	free(idx);
	heredoc_file.flags = O_CREAT | O_RDWR;
	heredoc_file.fd = open(heredoc_file.name, heredoc_file.flags, 0644);
	if (heredoc_file.fd == -1)
		return (free(heredoc_file.name), (t_file){.exists = FALSE});
	get_lines(head, &heredoc_file, eof);
	close(heredoc_file.fd);
	heredoc_file.exists = TRUE;
	return (heredoc_file);
}
