/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:20:07 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:20:08 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

void	ft_error(t_head *head, t_error error);

int		is_to_exit(int error_id);
void	print_error(t_msg msg);
int		get_exit_error_code(int error_id);
char	*get_error_description(t_head *head, t_error *error);

#endif