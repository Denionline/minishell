/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dximenes <dximenes@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:20:25 by dximenes          #+#    #+#             */
/*   Updated: 2025/11/20 11:21:57 by dximenes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	envp_size(char **envp)
{
	int	size;

	size = 0;
	while (envp && envp[size])
		size++;
	return (size);
}

static void	copy_envp(t_env *env, char **original)
{
	int	i;

	env->n_vars = envp_size(original);
	env->vars = ft_calloc(env->n_vars + 1, sizeof(char *));
	if (!env->vars)
		return ;
	i = 0;
	while (original && original[i])
	{
		env->vars[i] = ft_strdup(original[i]);
		i++;
	}
	env->vars[i] = NULL;
}

void	initializer(t_head **head, int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(*head) = ft_calloc(1, sizeof(t_head));
	if (!(*head))
		ft_error(NULL, (t_error){.id = ERR_MALLOC});
	ft_bzero(*head, sizeof(**head));
	copy_envp(&(*head)->env, envp);
	new_shlvl((*head)->env.vars);
}
