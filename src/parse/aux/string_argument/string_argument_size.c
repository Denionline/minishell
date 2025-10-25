
#include "minishell.h"

static int variable_size(char *string, char **envp, int i, int j)
{
	char	*prefix;
	char	*name;
	char	*val;
	int		name_len;
	int		size;
	
	size = 0;
	name_len = j - (i + 1);
	name = ft_calloc(name_len + 1, 1);
	if (!name)
		return (-1);
	ft_memcpy(name, string + 1, name_len);
	prefix = ft_strjoin(name, "=");
	free(name);
	if (prefix)
	{
		val = get_var_path(prefix, envp);
		free(prefix);
		if (val)
		{
			size = ft_strlen(val);
			free(val);
		}
	}
	return (size);
}

int	string_argument_size(char *string, char **envp, int to_expand, int is_hdoc)
{
	t_quotes	quotes;
	int			size;
	int			jumps;
	int			i;
	int			j;

	ft_bzero(&quotes, sizeof(quotes));
	jumps = 0;
	size = 0;
	i = -1;
	while (string[++i])
	{
		if (is_tohandle_backslash(string + jumps + i, quotes.quote))
			jumps += 1;
		if (is_quote_closed(&quotes) && get_operator(string + i) && !is_hdoc)
			break ;
		if (is_quote_closed(&quotes) && ft_isspace(string[i]) && !is_hdoc)
			break ;
		if (string[i] == '\'' || string[i] == '\"')
		{
			if (!verify_quotes(&quotes, string[i], is_hdoc))
				continue ;
		}
		if (string[i] == '$' && envp && quotes.quote != '\'' && to_expand)
		{
			j = i + 1;
			while (string[j] && is_var_char(string[j]))
				j++;
			size += variable_size(string + i, envp, i, j) - 1;
			i = j - 1;
		}
		size += 1;
	}
	return (size - jumps);
}
