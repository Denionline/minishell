
#include "minishell.h"

char	*string_argument(char *string, char **envp)
{
	t_arg	arg;
	char	quote;

	ft_bzero(&arg, sizeof(arg));
	arg.lstring = string_argument_size(string, envp);
	if (arg.lstring < 0)
		return (NULL);
	arg.string = ft_calloc(arg.lstring + 1, 1);
	if (!arg.string)
		return (NULL);
	quote = '\0';
	while (string[arg.i] && arg.pos < arg.lstring)
	{
		/* backslash handling (not active inside single quotes) */
		if (is_tohandle_backslash(string + arg.i, quote))
		{
			if (string[arg.i + 1])
			{
				arg.string[arg.pos++] = string[arg.i + 1];
				arg.i += 2;
				continue ;
			}
			/* trailing backslash */
			arg.string[arg.pos++] = '\\';
			arg.i++;
			continue ;
		}

		/* toggle quotes (do not copy quotes) */
		if (string[arg.i] == '\'' || string[arg.i] == '\"')
		{
			if (!quote)
				quote = string[arg.i];
			else if (quote == string[arg.i])
				quote = '\0';
			if (string[arg.i] == quote)
				arg.i++;
			continue ;
		}

		/* stop on unquoted operator or whitespace */
		if (!quote && get_operator(string + arg.i))
			break ;
		if (!quote && ft_isspace(string[arg.i]))
			break ;

		/* variable expansion */
		if (string[arg.i] == '$' && envp && quote != '\'')
		{
			/* special $? placeholder (example: '0') */
			if (string[arg.i + 1] && string[arg.i + 1] == '?')
			{
				arg.string[arg.pos++] = '0';
				arg.i += 2;
				continue ;
			}
			/* not followed by a character -> copy '$' */
			if (!string[arg.i + 1])
			{
				arg.string[arg.pos++] = '$';
				arg.i++;
				continue ;
			}
			/* not a var char after $ -> literal $ */
			if (!is_var_char(string[arg.i + 1]))
			{
				arg.string[arg.pos++] = '$';
				arg.i++;
				continue ;
			}
			/* collect var name */
			size_t j = arg.i + 1;
			while (string[j] && is_var_char(string[j]))
				j++;
			size_t name_len = j - (arg.i + 1);
			char *name = ft_calloc(name_len + 1, 1);
			if (!name)
			{
				free(arg.string);
				return (NULL);
			}
			ft_memcpy(name, string + arg.i + 1, name_len);
			char *prefix = ft_strjoin(name, "=");
			free(name);
			if (prefix)
			{
				char *val = get_var_path(prefix, envp);
				free(prefix);
				if (val)
				{
					size_t k = 0;
					while (val[k])
						arg.string[arg.pos++] = val[k++];
					free(val);
				}
			}
			arg.i = (int)j;
			continue ;
		}

		/* normal char copy */
		arg.string[arg.pos++] = string[arg.i++];
	}

	arg.string[arg.pos] = '\0';
	return (arg.string);
}
