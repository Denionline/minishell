/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:22:53 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:22:54 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_flag(char *string)
{
	const char	*flag = "-n";
	int			i;

	i = 2;
	if (!string || !string[0] || !string[1])
		return (FALSE);
	while (string[i])
	{
		if (string[i] != 'n')
			return (FALSE);
		i++;
	}
	if (!ft_strncmp(flag, string, ft_strlen(flag)))
		return (TRUE);
	return (FALSE);
}

int	ft_echo(t_cmd *cmd)
{
	int	flag_exists;
	int	i;

	flag_exists = FALSE;
	i = 0;
	while (cmd->args[++i])
	{
		if (i == 1 && is_flag(cmd->args[i]))
		{
			flag_exists = TRUE;
			continue ;
		}
		if (flag_exists && is_flag(cmd->args[i]) && is_flag(cmd->args[i - 1]))
			continue ;
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', 1);
	}
	if (!flag_exists)
		ft_putchar_fd('\n', 1);
	return (define_exit_code(0, TRUE));
}
