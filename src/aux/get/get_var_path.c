/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:21:35 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:21:35 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_path(char *prefix, char **envp)
{
	char	*name;
	int		lname;
	int		i;

	name = ft_strjoin(prefix, "=");
	lname = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, lname))
		{
			free(name);
			return (ft_strdup(envp[i] + lname));
		}
		i++;
	}
	free(name);
	return (NULL);
}
