/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:12:17 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 21:20:13 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_file(t_file *file, t_head *head, char *string, t_file data)
{
	if (data.exists)
	{
		if (file->name)
			free(file->name);
		if (data.flags < 0)
			(*file) = heredoc(head, string);
		else
		{
			file->name = ft_strdup(string);
			file->flags = data.flags;
			file->operator = data.operator;
			file->exists = TRUE;
			file->fd = open(string, data.flags, 0644);
			file->access = file->fd;
			if (file->fd != -1)
				close(file->fd);
			file->fd = -1;
		}
	}
	free(string);
}

static int	get_flags(int op)
{
	if (op == ARROW_LEFT)
		return (O_RDONLY);
	if (op == DOUBLE_ARROW_LEFT)
		return (-1);
	if (op == ARROW_RIGHT)
		return (O_CREAT | O_WRONLY | O_TRUNC);
	if (op == DOUBLE_ARROW_RIGHT)
		return (O_CREAT | O_WRONLY | O_APPEND);
	return (0);
}

static int	is_file_invalid(t_files *files)
{
	if (files)
	{
		if (files->in.exists && files->in.access == -1)
			return (TRUE);
		if (files->out.exists && files->out.access == -1)
			return (TRUE);
	}
	return (FALSE);
}

int	handle_file(t_head *head, t_files *files, char *prompt, int op)
{
	t_file	data;
	char	*string;
	int		pos;

	data = (t_file){
		.flags = get_flags(op),
		.exists = !(!files),
		.operator = op
	};
	if (is_file_invalid(files))
		data.exists = FALSE;
	pos = get_operator_size(op);
	while (ft_isspace(prompt[pos]))
		pos++;
	string = string_argument(head, prompt + pos,
			(t_arg){.len = &pos, .to_expand = (op != DOUBLE_ARROW_LEFT)});
	if (op == ARROW_LEFT)
		manage_file(&files->in, head, string, data);
	if (op == DOUBLE_ARROW_LEFT)
		manage_file(&files->in, head, string, data);
	if (op == ARROW_RIGHT)
		manage_file(&files->out, head, string, data);
	if (op == DOUBLE_ARROW_RIGHT)
		manage_file(&files->out, head, string, data);
	return (pos);
}
