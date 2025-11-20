/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_realloc_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:34:52 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:21:43 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_realloc_args(char **old_args, int new_len, char *new_value)
{
	char	**new_args;
	int		i;

	new_args = ft_calloc(new_len + 1, sizeof(char *));
	if (!new_args)
		return (NULL);
	if (old_args)
	{
		i = 0;
		while (old_args[i] && i < new_len)
		{
			new_args[i] = old_args[i];
			i++;
		}
		free(old_args);
	}
	if (new_value)
		new_args[new_len - 1] = new_value;
	new_args[new_len] = NULL;
	return (new_args);
}
