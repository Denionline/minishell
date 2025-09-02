/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:24:43 by dximenes          #+#    #+#             */
/*   Updated: 2025/09/02 15:05:18 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(t_head *head, char *prompt)
{
	(void)head;
	char	**values;
	int		i;

	values = ft_split(prompt, ' ');
	i = 0;
	while (values[i])
	{
		ft_putendl_fd(values[i], 1);
		i++;
	}
}
