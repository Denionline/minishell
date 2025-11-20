/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_error_code.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:09:36 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 12:20:24 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exit_error_code(int error_id)
{
	if (error_id == ERR_CMD || error_id == ERR_NOT_FOUND)
		return (127);
	if (error_id == ERR_PER || error_id == ERR_DIR)
		return (126);
	if (error_id == ERR_SYNTAX_ERROR || error_id == ERR_QUOTES_ERROR)
		return (2);
	return (1);
}
