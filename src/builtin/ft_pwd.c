/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clumertz <clumertz@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:22:28 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 19:15:28 by clumertz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	buffer[999];

	if (getcwd(buffer, 999) != NULL)
		ft_putendl_fd(buffer, 1);
	else
		return (define_exit_code(1, TRUE));
	return (define_exit_code(0, TRUE));
}
