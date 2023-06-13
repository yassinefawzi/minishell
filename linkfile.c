/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:52:18 by yfawzi            #+#    #+#             */
/*   Updated: 2023/06/07 16:11:55 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	ft_lstadd_back(t_args **alst, t_args *new)
{
	t_args	*last;

	if (alst)
	{
		if (*alst)
		{
			last = ft_lstlast(*alst);
			last->next = new;
		}
		else
			*alst = new;
	}
}

t_args	*ft_lstnew(char *arg)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (0);
	args->command = commandret(args);
	env->value = env_val(enva);
	env->next = 0;
	return (env);
}