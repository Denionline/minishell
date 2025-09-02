/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:33:50 by dximenes          #+#    #+#             */
/*   Updated: 2025/09/02 15:08:45 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell(t_head *head)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("\001\033[1;92m\002minishell\001\033[1;94m\002> \001\033[0;39m\002");
		parse(head, prompt);
	}
}
