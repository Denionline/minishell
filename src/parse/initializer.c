/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 12:00:28 by dximenes          #+#    #+#             */
/*   Updated: 2025/09/02 14:14:28 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initializer(t_head **head, int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(*head) = malloc(sizeof(t_head));
	if (!(*head))
		return ;
	ft_bzero(*head, sizeof(**head));
	(*head)->envp = envp;
}