
#include "minishell.h"

static int	get_size_file(char *prompt, int op_size)
{
	int	size;

	size = op_size;
	while (ft_isspace(prompt[size]))
		size += 1;
	while (prompt[size])
	{
		if (ft_isspace(prompt[size]))
			break ;
		size++;
	}
	return (size);
}

static int	next_increase(int operator, char *prompt)
{
	if (operator == AND)
		return (operator_size(operator));
	if (operator == OR)
		return (operator_size(operator));
	if (operator == DOUBLE_ARROW_LEFT)
		return (operator_size(operator));
	if (operator == DOUBLE_ARROW_RIGHT)
		return (get_size_file(prompt, operator_size(operator)));
	if (operator == ARROW_RIGHT)
		return (get_size_file(prompt, operator_size(operator)));
	if (operator == ARROW_LEFT)
		return (get_size_file(prompt, operator_size(operator)));
	return (1);
}

static char	*ft_strreplace(char *string, char search)
{
	char	*new_string;
	int		j;
	int		i;

	if (!string)
		return (NULL);
	if (search == '\0')
		return (string);
	i = 0;
	j = 0;
	while (string && string[j])
	{
		if (search && string[j] == search)
			i++;
		j++;
	}
	j -= i;
	new_string = ft_calloc(j + 1, 1);
	if (!new_string)
		return (NULL);
	j = 0;
	i = 0;
	while (string && string[i])
	{
		if (search && string[i] != search)
			new_string[j++] = string[i];
		i++;
	}
	new_string[j] = '\0';
	free(string);
	return (new_string);
}

static char	**realloc_args(char **old_args, int new_len)
{
	char	**new_args;
	int		i;

	new_args = ft_calloc(new_len + 1, sizeof(char *));
	if (!new_args)
		return (NULL);
	if (old_args)
	{
		i = 0;
		while (old_args[i])
		{
			new_args[i] = old_args[i];
			i++;
		}
		free(old_args);
	}
	return (new_args);
}

static void	verify_quotes(t_quotes *quotes, char c)
{
	if (c == '\'')
		quotes->s += 1;
	if (c == '\"')
		quotes->d += 1;
	if (!quotes->quote)
		quotes->quote = c;
	else if (quotes->quote == c)
		quotes->quote = '\0';
}

static int	is_main_quote_closed(t_quotes *quotes)
{
	if (!quotes->quote)
		return (TRUE);
	if (quotes->quote == '\'' && (quotes->s % 2) == 0)
		return (TRUE);
	if (quotes->quote == '\"' && (quotes->d % 2) == 0)
		return (TRUE);
	return (FALSE);
}

static char	*get_arg(char *string, t_quotes *quotes)
{
	char	quote;
	char	*arg;
	int		size;
	int		i;

	size = 0;
	while (string[size])
	{
		if (quotes->quote)
			quote = quotes->quote;
		if (is_main_quote_closed(quotes) && is_operator(string + size))
			break ;
		if (is_main_quote_closed(quotes) && ft_isspace(string[size]))
			break ;
		if (string[size] == '\'' || string[size] == '\"')
			verify_quotes(quotes, string[size]);
		size++;
	}
	arg = ft_calloc(size + 1, 1);
	if (!arg)
		return (NULL);
	i = 0;
	while (i < size)
	{
		arg[i] = string[i];
		i++;
	}
	arg[i] = '\0';
	return (ft_strreplace(arg, quote));
}

char	**get_cmd_args(char *prompt)
{
	t_quotes	quotes;
	char		**args;
	int			size_args;
	int			operator;
	int			i;

	if (!prompt || !*prompt)
		return (NULL);
	ft_bzero(&quotes, sizeof(quotes));
	if (ft_isspace(prompt[0]))
		prompt++;
	args = NULL;
	size_args = 0;
	i = 0;
	while (prompt[i])
	{
		operator = is_operator(prompt + i);
		if (operator)
			break ;
		if (operator == DOUBLE_ARROW_RIGHT || operator == ARROW_RIGHT)
			prompt += next_increase(operator, prompt + i);
		if (!ft_isspace(prompt[i]) && (i == 0 || ft_isspace(prompt[i - 1])))
		{
			args = realloc_args(args, size_args + 1);
			args[size_args] = get_arg(prompt + i, &quotes);
			prompt += ft_strlen(args[size_args++]);
			i = 0;
		}
		i++;
	}
	return (args);
}
