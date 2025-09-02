
#include "minishell.h"

void	parse(t_head *head, char *prompt)
{
	(void)head;
	char	**values;
	int		i;

	values = ft_split(prompt, ' ');
	i = 0;
	while (values[i])
	{
		ft_putendl_fd(values[i], 1);
		i++;
	}
}
