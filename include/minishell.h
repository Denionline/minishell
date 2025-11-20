/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:42:09 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:56:06 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <signal.h>

# include "libft/include/libft.h"

# include "structs.h"
# include "parser.h"
# include "execute.h"
# include "builtin.h"
# include "error.h"
# include "auxiliary.h"
# include "binary_tree.h"
# include "signals.h"
# include "colors.h"

void	initializer(t_head **head, int argc, char *argv[], char *envp[]);
int		minishell(t_head *head);
void	prompt_prefix(char buffer[9999]);

#endif
