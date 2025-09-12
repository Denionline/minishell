/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:34:50 by dximenes          #+#    #+#             */
/*   Updated: 2025/09/12 11:36:34 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_size_string_command(char *string)
{
	int		i;
	
	i = 0;
	while (string[i] && !is_operator(string + i))
		i++;
	return (i);
}

static char	*get_string_command(char *string_command)
{
	const int	string_size = get_size_string_command(string_command);
	char		*string;
	int			i;

	string = ft_calloc(1, string_size + 1);
	if (!string)
		return (NULL);
	i = 0;
	while (string_command[i] && !is_operator(string_command + i))
	{
		string[i] = string_command[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

char	**get_args(char *prompt)
{
	char	*string_command;

	string_command = get_string_command(prompt);
}