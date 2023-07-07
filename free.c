/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:42:17 by yfawzi            #+#    #+#             */
/*   Updated: 2023/07/08 00:54:29 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		free(env->name);
		free(env->value);
		env = env->next;
		free(tmp);
		tmp = env;
	}
}

void	ft_free(t_args *args)
{
	int		i;
	t_args	*tmp;
	t_args	*tmp1;

	tmp = args;
	i = 0;
	while (tmp)
	{
		while (tmp->command[i])
			free(tmp->command[i++]);
		i = 0;
		free(tmp->command);
		tmp1 = tmp;
		tmp = tmp->next;
		free(tmp1);
	}
}