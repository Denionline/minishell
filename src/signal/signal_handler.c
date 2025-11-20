/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:11:17 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 19:17:52 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_handle_ctrl_c);
	signal(SIGPIPE, SIG_IGN);
}

void	ft_handle_ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	define_exit_code(130, TRUE);
}

void	child_signal_handler(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGPIPE, ft_sigpipe_child);
}

void	ft_ctrl_c_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
	define_exit_code(130, TRUE);
}

void	ft_sigpipe_child(int sig)
{
	(void)sig;
	define_exit_code(141, TRUE);
}
