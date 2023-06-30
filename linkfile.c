/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:52:18 by yfawzi            #+#    #+#             */
/*   Updated: 2023/06/30 01:34:24 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_args	*ft_lstlast(t_args *list)
{
	while (list)
	{
		if (!list->next)
			return (list);
		list = list->next;
	}
	return (list);
}

void	ft_lstadd_back(t_args **list, t_args *new)
{
	t_args	*last;

	if (!new)
		return ;
	if (list)
	{
		if (*list)
		{
			last = ft_lstlast(*list);
			last->next = new;
		}
		else
			*list = new;
	}
}

t_args	*ft_lstnew_args(char *arg)
{
	t_args	*args;
	char	*str;

	if (!arg)
		return (0);
	args = malloc(sizeof(t_args));
	if (!args)
		return (0);
	args->command = ft_split(arg, ' ');
	args->next = 0;
	return (args);
}