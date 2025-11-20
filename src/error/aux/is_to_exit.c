/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_to_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:37:57 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:37:57 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_to_exit(int error_id)
{
	if (error_id == ERR_CD)
		return (FALSE);
	if (error_id == ERR_MAX_ARGS)
		return (FALSE);
	if (error_id == ERR_SYNTAX_ERROR)
		return (FALSE);
	if (error_id == ERR_QUOTES_ERROR)
		return (FALSE);
	if (error_id == ERR_HOME_OLDPWD)
		return (FALSE);
	if (error_id == ERR_EXPORT)
		return (FALSE);
	return (TRUE);
}
