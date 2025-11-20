/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_argument.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:10:41 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 12:10:51 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_to_handle_variable(t_arg *arg, char *s, char **envp, int expand)
{
	if (!expand)
		return (FALSE);
	if (!envp)
		return (FALSE);
	if (s[0] == '$' && arg->quotes.quote != '\'')
	{
		if (s[1] == '?')
			return (TRUE);
		if (!s[1])
			return (FALSE);
		if (!is_var_char(s[1], 0))
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

static int	variable(t_arg *arg, char *string, t_head *head)
{
	char	*variable;
	char	*name;
	int		var_size;
	int		i;

	arg->was_expanded = TRUE;
	var_size = 1;
	while (string[var_size] && is_var_char(string[var_size], var_size))
		var_size++;
	if (string[1] == '?' )
		var_size = 2;
	name = ft_substr(string, 1, var_size - 1);
	if (!name)
		return (free(arg->string), 0);
	if (string[1] == '?')
		variable = ft_itoa(define_exit_code(0, FALSE));
	else
		variable = get_var_path(name, head->env.vars);
	if (!variable)
		return (free(name), var_size);
	i = 0;
	while (variable[i])
		arg->string[arg->pos++] = variable[i++];
	return (free(name), free(variable), var_size);
}

static char	*get_string_verified(t_arg *arg)
{
	if (!(*arg->string) && arg->was_expanded)
	{
		free(arg->string);
		return (NULL);
	}
	return (arg->string);
}

static char	*argument_verification(t_arg *arg, char *string, t_head *head)
{
	if (is_tohandle_backslash(string, arg->quotes.quote))
		string++;
	else
	{
		if (*string == '\'' || *string == '\"')
			if (verify_quotes(&arg->quotes, *string, !arg->len))
				return (string);
	}
	if (is_quote_closed(&arg->quotes) && get_operator(string) && arg->len)
		return (NULL);
	if (is_quote_closed(&arg->quotes) && ft_isspace(*string) && arg->len)
		return (NULL);
	if (is_to_handle_variable(arg, string, head->env.vars, arg->to_expand))
		return (string + (variable(arg, string, head) - 1));
	arg->string[arg->pos++] = *string;
	return (string);
}

char	*string_argument(t_head *head, char *string, t_arg arg)
{
	char	*string_updated;
	int		add_quote;
	int		i;

	string_argument_size(&arg, string, head->env.vars);
	arg.quotes = (t_quotes){};
	arg.string = ft_calloc(arg.lstring + 1, 1);
	if (!arg.string)
		return (NULL);
	i = 0;
	while (string[i] && arg.pos < arg.lstring)
	{
		string_updated = argument_verification(&arg, string + i, head);
		if (!string_updated)
			break ;
		if (string_updated - string)
			i = (string_updated - string);
		i += 1;
	}
	add_quote = (arg.pos > 0 && arg.string[arg.pos - 1] == arg.quotes.quote);
	arg.string[arg.pos - add_quote] = '\0';
	if (arg.len && arg.to_expand)
		*(arg.len) += i + add_quote;
	return (get_string_verified(&arg));
}
