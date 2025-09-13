/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 11:35:52 by dximenes          #+#    #+#             */
/*   Updated: 2025/09/13 15:51:45 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_command(t_cmd *cmd)
{
	printf("path: %s and args:", cmd->path);
	for (int i = 0; cmd->args[i]; i++) {
		printf(" arg[%d]: %s", i, cmd->args[i]);
	}
	printf("\n");
}

void	print(t_token *token)
{
	if (token->left)
		print(token->left);
	if (token->cmd)
		print_command(token->cmd);
	else
		printf("%s\n", token->identifier);
	if (token->right)
		print(token->right);
}
