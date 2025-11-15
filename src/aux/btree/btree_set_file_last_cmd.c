#include "minishell.h"

static void	set_or_replace_file(t_file *to_change, t_file *source)
{
	if (to_change->name)
		free(to_change->name);
	*to_change = (t_file){};
	to_change->name = source->name;
	to_change->exists = source->exists;
	to_change->flags = source->flags;
	to_change->fd = source->fd;
	to_change->operator = source->operator;
	to_change->is_there_heredoc = source->is_there_heredoc;
	(*source) = (t_file){.fd = -1, .access = source->access};
}

static void	check_to_change(t_btree **node, t_files **files)
{
	if ((*files)->in.exists)
		set_or_replace_file(&(*node)->files.in, &(*files)->in);
	if ((*files)->out.exists)
		set_or_replace_file(&(*node)->files.out, &(*files)->out);
}

void	btree_set_file_last_cmd(t_btree **root, t_files **files)
{
	if (*root)
	{
		if ((*root)->right)
			return (check_to_change(&(*root)->right, files));
		else
			return (check_to_change(root, files));
	}
}
