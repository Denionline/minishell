/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:31:08 by dximenes          #+#    #+#             */
/*   Updated: 2025/09/02 12:32:44 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <stdlib.h>
#include "libft/include/libft.h"

typedef struct s_inputs
{
	char	**envp;
}	t_inputs;

typedef struct s_head
{
	char	**envp;
}	t_head;

void	initializer(t_head **head);
void	parse(t_head *head, int argc, char *argv[], char *envp[]);
int		minishell(t_head *head);

#endif