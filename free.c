/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 02:42:17 by yfawzi            #+#    #+#             */
/*   Updated: 2023/05/31 02:52:12 by yfawzi           ###   ########.fr       */
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