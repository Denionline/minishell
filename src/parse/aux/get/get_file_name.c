
#include "minishell.h"

char	*get_file_name(char *prompt, int op_size, int file_size)
{
	char	*file_name;
	int		i;

	prompt += op_size;
	file_size -= op_size;
	while (ft_isspace(prompt[0]))
	{
		file_size -= 1;
		prompt++;
	}
	file_name = ft_calloc(file_size + 1, 1);
	if (!file_name)
		return (NULL);
	i = 0;
	while (i < file_size)
	{
		file_name[i] = prompt[i];
		i++;
	}
	file_name[i] = '\0';
	return (file_name);
}
