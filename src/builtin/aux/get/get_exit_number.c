/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:33:20 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 19:15:45 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exit_number(t_btree *node)
{
	long long	n;

	n = ft_atoll(node->cmd->args[1]);
	if ((n == LLONG_MAX || n == LLONG_MIN) && confirm_llong(node->cmd->args[1]))
		return (n);
	else if (n > 0 && n < 255)
		return (n);
	else if (n < LLONG_MAX && n > 255)
		return (n % 256);
	else if (n > LLONG_MIN && n < 0)
		return (256 + (n % 256));
	else
		return (error_num_required(node));
}
