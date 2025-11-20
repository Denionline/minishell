/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:56:50 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 10:57:32 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	signal_handler(void);
void	ft_handle_ctrl_c(int sig);
void	child_signal_handler(void);
void	ft_ctrl_c_heredoc(int sig);
void	ft_sigpipe_child(int sig);

#endif