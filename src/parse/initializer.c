
#include "minishell.h"

static int	envp_size(char **envp)
{
	int	size;

	size = 0;
	while (envp && envp[size])
		size++;
	return (size);
}

static char	**copy_envp(char **original_envp)
{
	const int	original_envp_size = envp_size(original_envp);
	char		**copy_envp;
	int			i;

	copy_envp = ft_calloc(original_envp_size, sizeof(char *));
	if (!copy_envp)
		return (NULL);
	i = -1;
	while (original_envp && original_envp[++i])
		copy_envp[i] = ft_strdup(original_envp[i]);
	copy_envp[i] = NULL;
	return (copy_envp);
}

void	initializer(t_head **head, int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(*head) = malloc(sizeof(t_head));
	if (!(*head))
		end(*head, errno, "head");
	ft_bzero(*head, sizeof(**head));
	(*head)->envp = copy_envp(envp);
}