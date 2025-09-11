/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 19:15:51 by dximenes          #+#    #+#             */
/*   Updated: 2025/09/10 16:43:27 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_valid_path(char **paths, char *command)
{
	char	*complete_path;
	char	*path_bar;
	int		j;

	j = 0;
	while (paths[j])
	{
		path_bar = ft_strjoin(paths[j], "/");
		complete_path = ft_strjoin(path_bar, command);
		free(path_bar);
		if (!access(complete_path, F_OK))
			return (complete_path);
		free(complete_path);
		j++;
	}
	return (NULL);
}

char	**get_paths(char *env[])
{
	const char	*prefix = "PATH=";
	const int	lprefix = ft_strlen(prefix);
	int			i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], prefix, lprefix))
			return (ft_split(env[i] + lprefix, ':'));
		i++;
	}
	return (NULL);
}
