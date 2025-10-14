
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
	ft_memcpy(name, string + i + 1, name_len);
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

int	string_argument_size(char *string, char **envp)
{
	t_quotes	quotes;
	int			size;
	int			j;
	int			i;

	i = -1;
	size = 0;
	ft_bzero(&quotes, sizeof(quotes));
	while (string[++i])
	{
		if (is_tohandle_backslash(string + i, quotes.quote))
		{
			size += 1;
			if (string[i + 1])
				i += 1;
			continue ;
		}
		if (string[i] == '\'' || string[i] == '\"')
		{
			if (string[i] != quotes.quote)
				size++;
			if (!quotes.quote)
				quotes.quote = string[i];
			else if (quotes.quote == string[i])
				quotes.quote = '\0';
			continue ;
		}
		if (!quotes.quote && get_operator(string + i))
			break ;
		if (!quotes.quote && ft_isspace(string[i]))
			break ;
		if (string[i] == '$' && envp && quotes.quote != '\'')
		{
			if (string[i + 1] && string[i + 1] == '?' && ++i && ++size)
				continue ;
			if (!string[i + 1] && ++size)
				continue ;
			if (!is_var_char(string[i + 1]) && ++size)
				continue ;
			j = i + 1;
			while (string[j] && is_var_char(string[j]))
				j++;
			size += variable_size(string, envp, i, j);
			i = j;
			continue ;
		}
		size++;
	}
	return (size);
}
