
#include "minishell.h"
#include "structs.h"

static t_file	*realloc_files(t_file *files_array, t_file *source)
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
	reallocated_files[i++] = (t_file){
		.name = ft_strdup(source->name),
		.exists = source->exists,
		.flags = source->flags,
		.fd = source->fd,
	};
	reallocated_files[i] = (t_file){.fd = -1};
	free(files_array);
	(*source) = (t_file){.fd = -1};
	return (reallocated_files);
}

static void	check_to_change(t_btree **node, t_files **files)
{
	if ((*files)->in[0].exists)
		(*node)->files.in = realloc_files((*node)->files.in, (*files)->in);
	if ((*files)->out[0].exists)
		(*node)->files.out = realloc_files((*node)->files.out, (*files)->out);
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
