/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfawzi <yfawzi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:08:55 by yfawzi            #+#    #+#             */
/*   Updated: 2023/06/07 16:11:19 by yfawzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*commandret(char *str)
{
	int		i;
	char	*str1;

	str1 = malloc(ft_strlen(str));
	i = 0;
	while (str[i] && str[i] != '|')
	{
		str1[i] = str[i];
		i++;
	}
	return (str1);
}