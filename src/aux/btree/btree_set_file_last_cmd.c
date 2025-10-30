
#include "minishell.h"

static t_file	*realloc_files(t_file *files_array, t_file new_file)
{
	t_file	*reallocated_files;
	int		i;

	i = 0;
	while (files_array[i].exists)
		i++;
	reallocated_files = ft_calloc(i + 2, sizeof(t_file));
	if (!reallocated_files)
		return (&(t_file){});
	i = -1;
	while (files_array[++i].exists)
		reallocated_files[i] = files_array[i];
	reallocated_files[i++] = new_file;
	reallocated_files[i] = (t_file){};
	free(files_array);
	return (reallocated_files);
}

static void	set_or_replace_file(t_file **to_change, t_file *source)
{
	(*to_change) = realloc_files((*to_change),
		(t_file){
			.name = ft_strdup(source->name),
			.exists = source->exists,
			.flags = source->flags,
			.fd = source->fd
		}
	);
	(*source) = (t_file){};
}

static void	check_to_change(t_btree **node, t_files **files)
{
	if ((*files)->in[0].exists)
		set_or_replace_file((*node)->files.in, (*files)->in);
	if ((*files)->out[0].exists)
		set_or_replace_file((*node)->files.out, (*files)->out);
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
