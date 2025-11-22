/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:09:28 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/22 14:23:34 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len(t_msg *msg)
{
	int	len;

	len = 0;
	len += sizeof("minishell: ") - 1;
	if (msg->where)
		len += ft_strlen(msg->where) + 2;
	if (msg->argument)
	{
		if (!(*msg->argument))
			len += 2;
		else
			len += ft_strlen(msg->argument);
		len += 2;
	}
	len += ft_strlen(msg->error_description);
	len += 1;
	return (len);
}

static void	put_arguments(char **buff, t_msg *msg, int len)
{
	if (msg->where)
	{
		ft_strlcat((*buff), msg->where, len + 1);
		ft_strlcat((*buff), ": ", len + 1);
	}
	if (msg->argument)
	{
		if (!(*msg->argument))
			ft_strlcat((*buff), "''", len + 1);
		else
			ft_strlcat((*buff), msg->argument, len + 1);
		ft_strlcat((*buff), ": ", len + 1);
	}
	ft_strlcat((*buff), msg->error_description, len + 1);
}

void	print_error(t_msg msg)
{
	char	*buf;
	int		len;

	if (!msg.error_description)
		return ;
	len = get_len(&msg);
	buf = ft_calloc(len + 1, 1);
	if (!buf)
		return ;
	ft_strlcat(buf, "minishell: ", len + 1);
	put_arguments(&buf, &msg, len);
	ft_strlcat(buf, "\n", len + 1);
	write(2, buf, ft_strlen(buf));
	free(buf);
}
