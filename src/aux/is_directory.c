/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:22:14 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:22:15 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(char *string)
{
	DIR	*dir;

	if (ft_strchr(string, '/'))
	{
		dir = opendir(string);
		if (dir)
		{
			closedir(dir);
			return (TRUE);
		}
	}
	return (FALSE);
}
