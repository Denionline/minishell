
#include "minishell.h"

static int	is_to_handle_variable(t_arg *arg, char *s, char quote, char **envp)
{
	if (!envp)
		return (FALSE);
	if (s[arg->i] == '$' && quote != '\'')
	{
		if (!s[arg->i + 1])
			return (FALSE);
		if (!is_var_char(s[arg->i + 1]))
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

static void	variable(t_arg *arg, char *string, char **envp, int j)
{
	char	*prefix;
	char	*name;
	char	*val;
	int		name_len;
	int		k;

	name_len = j - (arg->i + 1);
	name = ft_substr(string + arg->i + 1, 0, name_len);
	if (!name)
		return (free(arg->string));
	prefix = ft_strjoin(name, "=");
	free(name);
	if (prefix)
	{
		val = get_var_path(prefix, envp);
		free(prefix);
		if (val)
		{
			k = 0;
			while (val[k])
				arg->string[arg->pos++] = val[k++];
			free(val);
		}
	}
}

char	*string_argument(char *string, char **envp)
{
	t_quotes	quotes;
	t_arg		arg;
	int			j;

	ft_bzero(&arg, sizeof(arg));
	ft_bzero(&quotes, sizeof(quotes));
	arg.lstring = string_argument_size(string, envp);
	arg.string = ft_calloc(arg.lstring + 1, 1);
	if (!arg.string)
		return (NULL);
	arg.i = -1;
	while (string[++arg.i] && arg.pos < arg.lstring + arg.lvariables)
	{
		if (is_tohandle_backslash(string + arg.i, quotes.quote))
		{
			if (string[arg.i + 1])
			{
				arg.string[arg.pos++] = string[++arg.i];
				continue ;
			}
			arg.string[arg.pos++] = '\\';
			continue ;
		}
		if (string[arg.i] == '\'' || string[arg.i] == '\"')
		{
			if (verify_quotes(&quotes, string[arg.i]))
				arg.string[arg.pos++] = string[arg.i];
			continue ;
		}
		if (is_main_quote_closed(&quotes) && get_operator(string + arg.i))
			break ;
		if (is_main_quote_closed(&quotes) && ft_isspace(string[arg.i]))
			break ;
		if (is_to_handle_variable(&arg, string, quotes.quote, envp))
		{
			j = arg.i + 1;
			while (string[j] && is_var_char(string[j]))
				j++;
			variable(&arg, string, envp, j);
			arg.i = j - 1;
			continue ;
		}
		arg.string[arg.pos++] = string[arg.i];
	}
	arg.string[arg.pos] = '\0';
	return (arg.string);
}
//  "e"c'h'"o" "hel' $SHELL 'lo"