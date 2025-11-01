
#include "minishell.h"
#include "structs.h"

static void	set_or_replace_file(t_file *to_change, t_file *source)
{
	if (to_change->name)
		free(to_change->name);
	ft_bzero(to_change, sizeof(*to_change));
	to_change->name = ft_strdup(source->name);
	to_change->exists = source->exists;
	to_change->flags = source->flags;
	to_change->fd = source->fd;
	to_change->access = source->access;
	(*source) = (t_file){.fd = -1};
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
		if ((*root)->right && (*root)->right->identifier == COMMAND)
			return (check_to_change(&(*root)->right, files));
		else if ((*root)->identifier == COMMAND)
			return (check_to_change(root, files));
	}
}
